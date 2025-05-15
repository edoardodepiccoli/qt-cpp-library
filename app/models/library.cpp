#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QFileInfo>
#include <QImage>

#include "library.h"
#include "../visitors/jsonvisitor.h"

Library::Library()
{
    ensureImagesDirectoryExists();
    loadFromFile();
}

void Library::addItem(std::unique_ptr<Item> item)
{
    if (!item)
        return;

    items.push_back(std::move(item));
    saveToFile();
}

void Library::removeItem(const QUuid &id)
{
    auto it = std::find_if(items.begin(), items.end(),
                           [&id](const std::unique_ptr<Item> &item)
                           {
                               return item->getId() == id;
                           });

    if (it != items.end())
    {
        // Remove the image file if it exists and is in our local images directory
        QString imagePath = (*it)->getImagePath();
        qDebug() << "Checking image path for deletion:" << imagePath;
        qDebug() << "Images path from Library:" << imagesPath;

        if (!imagePath.isEmpty() && QFile::exists(imagePath))
        {
            QFileInfo fileInfo(imagePath);
            QFileInfo imagesDirInfo(imagesPath);

            qDebug() << "Image absolute path:" << fileInfo.absolutePath();
            qDebug() << "Image directory:" << fileInfo.dir().absolutePath();
            qDebug() << "Images directory path:" << imagesDirInfo.absolutePath();

            // Check if the image is in our images directory
            QString imageDir = fileInfo.dir().absolutePath();
            QString targetDir = QFileInfo(imagesPath).absolutePath() + "/images";

            qDebug() << "Comparing directories:";
            qDebug() << "  Image dir:" << imageDir;
            qDebug() << "  Target dir:" << targetDir;

            if (imageDir == targetDir)
            {
                bool removed = QFile::remove(imagePath);
                qDebug() << "Attempted to delete image:" << imagePath << "Success:" << removed;
            }
            else
            {
                qDebug() << "Image not in images directory, skipping deletion";
            }
        }
        else
        {
            qDebug() << "No image path or file doesn't exist";
        }

        items.erase(it);
        saveToFile();
    }
}

void Library::removeItem(int index)
{
    if (index >= 0 && index < static_cast<int>(items.size()))
    {
        // Remove the image file if it exists and is in our local images directory
        QString imagePath = items[index]->getImagePath();
        qDebug() << "Checking image path for deletion:" << imagePath;
        qDebug() << "Images path from Library:" << imagesPath;

        if (!imagePath.isEmpty() && QFile::exists(imagePath))
        {
            QFileInfo fileInfo(imagePath);
            QFileInfo imagesDirInfo(imagesPath);

            qDebug() << "Image absolute path:" << fileInfo.absolutePath();
            qDebug() << "Image directory:" << fileInfo.dir().absolutePath();
            qDebug() << "Images directory path:" << imagesDirInfo.absolutePath();

            // Check if the image is in our images directory
            QString imageDir = fileInfo.dir().absolutePath();
            QString targetDir = QFileInfo(imagesPath).absolutePath() + "/images";

            qDebug() << "Comparing directories:";
            qDebug() << "  Image dir:" << imageDir;
            qDebug() << "  Target dir:" << targetDir;

            if (imageDir == targetDir)
            {
                bool removed = QFile::remove(imagePath);
                qDebug() << "Attempted to delete image:" << imagePath << "Success:" << removed;
            }
            else
            {
                qDebug() << "Image not in images directory, skipping deletion";
            }
        }
        else
        {
            qDebug() << "No image path or file doesn't exist";
        }

        items.erase(items.begin() + index);
        saveToFile();
    }
}

Item *Library::getItem(const QUuid &id) const
{
    auto it = std::find_if(items.begin(), items.end(),
                           [&id](const std::unique_ptr<Item> &item)
                           {
                               return item->getId() == id;
                           });

    return it != items.end() ? it->get() : nullptr;
}

Item *Library::getItem(int index) const
{
    if (index >= 0 && index < static_cast<int>(items.size()))
    {
        return items[index].get();
    }
    return nullptr;
}

int Library::getItemCount() const
{
    return static_cast<int>(items.size());
}

void Library::ensureImagesDirectoryExists()
{
    QDir dir(imagesPath);
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
}

QString Library::copyImageToDb(const QString &sourcePath, const QUuid &itemId)
{
    QFileInfo sourceFile(sourcePath);
    QString extension = sourceFile.suffix();
    if (extension.isEmpty())
    {
        extension = "png"; // Default to PNG if no extension
    }

    QString targetPath = QString("%1/%2.%3").arg(imagesPath).arg(itemId.toString()).arg(extension);

    // If the source is already in our db directory, no need to copy
    if (sourcePath == targetPath)
    {
        return targetPath;
    }

    QFile::remove(targetPath); // Remove existing file if any
    if (QFile::copy(sourcePath, targetPath))
    {
        return targetPath;
    }
    return QString();
}

QString Library::setItemImage(const QUuid &id, const QString &sourceImagePath)
{
    Item *item = getItem(id);
    if (!item)
    {
        qDebug() << "Item not found";
        return QString();
    }

    QString newImagePath = copyImageToDb(sourceImagePath, id);
    if (!newImagePath.isEmpty())
    {
        qDebug() << "New image path:" << newImagePath;
        item->setImagePath(newImagePath);
        saveToFile();
    }
    else
    {
        qDebug() << "Failed to copy image";
    }
    return newImagePath;
}

QString Library::getDefaultImagePath(const Item *item) const
{
    if (!item)
    {
        return "app/db/default.png";
    }

    // Return type-specific default images
    if (dynamic_cast<const Book *>(item))
    {
        return "app/db/default_book.png";
    }
    else if (dynamic_cast<const Movie *>(item))
    {
        return "app/db/default_movie.png";
    }
    else if (dynamic_cast<const Article *>(item))
    {
        return "app/db/default_article.png";
    }

    return "app/db/default.png";
}

void Library::removeItemImage(const QUuid &id)
{
    Item *item = getItem(id);
    if (!item)
    {
        return;
    }

    QString currentImagePath = item->getImagePath();
    if (!currentImagePath.isEmpty() && QFile::exists(currentImagePath))
    {
        QFile::remove(currentImagePath);
    }

    item->setImagePath(QString());
    saveToFile();
}

bool Library::saveToFile()
{
    QJsonArray jsonArray;
    JSONVisitor jsonVisitor;

    for (const auto &item : items)
    {
        item->accept(jsonVisitor);
        QJsonObject obj = jsonVisitor.getResult();
        obj["imagePath"] = item->getImagePath();
        jsonArray.append(obj);
    }

    QJsonDocument doc(jsonArray);
    QFile file(dbPath);

    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file.write(doc.toJson());
    return true;
}

bool Library::loadFromFile()
{
    QFile file(dbPath);
    if (!file.open(QIODevice::ReadOnly))
    {
        // If file doesn't exist, create an empty one
        if (!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
        QJsonArray emptyArray;
        QJsonDocument doc(emptyArray);
        file.write(doc.toJson());
        file.close();
        return true;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull())
    {
        return false;
    }

    QJsonArray jsonArray = doc.array();
    items.clear();

    for (const QJsonValue &value : jsonArray)
    {
        QJsonObject obj = value.toObject();
        QString type = obj["type"].toString();

        std::unique_ptr<Item> item;
        if (type == "book")
        {
            item = std::make_unique<Book>();
            static_cast<Book *>(item.get())->setAuthor(obj["author"].toString());
        }
        else if (type == "movie")
        {
            item = std::make_unique<Movie>();
            static_cast<Movie *>(item.get())->setDirector(obj["director"].toString());
        }
        else if (type == "article")
        {
            item = std::make_unique<Article>();
            static_cast<Article *>(item.get())->setLink(obj["link"].toString());
            static_cast<Article *>(item.get())->setAuthor(obj["author"].toString());
        }

        if (item)
        {
            if (obj.contains("id") && !obj["id"].isNull())
            {
                QUuid loadedId(obj["id"].toString());
                if (!loadedId.isNull())
                {
                    item->setId(loadedId);
                }
                else
                {
                    item->setId(QUuid::createUuid());
                }
            }
            else
            {
                item->setId(QUuid::createUuid());
            }

            item->setTitle(obj["title"].toString());
            item->setDescription(obj["description"].toString());
            item->setYear(obj["year"].toInt());
            item->setReview(obj["review"].toInt());
            item->setComment(obj["comment"].toString());

            // Load image path if it exists
            if (obj.contains("imagePath") && !obj["imagePath"].isNull())
            {
                item->setImagePath(obj["imagePath"].toString());
            }

            items.push_back(std::move(item));
        }
    }

    return true;
}

bool Library::updateItem(const QUuid &id, std::unique_ptr<Item> newItem)
{
    auto it = std::find_if(items.begin(), items.end(),
                           [&id](const std::unique_ptr<Item> &item)
                           {
                               return item->getId() == id;
                           });

    if (it != items.end())
    {
        // Only remove old image if the new item has a different image path
        QString oldImagePath = (*it)->getImagePath();
        QString newImagePath = newItem->getImagePath();

        if (!oldImagePath.isEmpty() && oldImagePath != newImagePath && QFile::exists(oldImagePath))
        {
            QFile::remove(oldImagePath);
        }

        newItem->setId(id);
        *it = std::move(newItem);
        saveToFile();
        return true;
    }
    return false;
}

void Library::accept(Visitor &visitor)
{
    int index = 0;
    for (const auto &item : items)
    {
        out << "index: " << (index + 1) << "\n";
        item->accept(visitor);
        index++;
    }
}

std::vector<Item *> Library::searchItems(const QString &query) const
{
    // Default to showing all items if query is empty, no logic in the mainwindow = we are really happy
    if (query.isEmpty())
    {
        std::vector<Item *> results;
        for (const auto &item : items)
        {
            results.push_back(item.get());
        }
        return results;
    }

    std::vector<Item *> results;
    QString lowerQuery = query.toLower();

    for (const auto &item : items)
    {
        if (!item)
            continue; // Skip null items

        // Search in common fields
        if (item->getTitle().toLower().contains(lowerQuery) ||
            item->getDescription().toLower().contains(lowerQuery) ||
            item->getComment().toLower().contains(lowerQuery) ||
            QString::number(item->getYear()).contains(lowerQuery) ||
            QString::number(item->getReview()).contains(lowerQuery))
        {
            results.push_back(item.get());
            continue;
        }

        // Search in specific fields based on item type
        if (auto book = dynamic_cast<Book *>(item.get()))
        {
            if (book->getAuthor().toLower().contains(lowerQuery))
            {
                results.push_back(item.get());
                continue;
            }
        }
        else if (auto movie = dynamic_cast<Movie *>(item.get()))
        {
            if (movie->getDirector().toLower().contains(lowerQuery))
            {
                results.push_back(item.get());
                continue;
            }
        }
        else if (auto article = dynamic_cast<Article *>(item.get()))
        {
            if (article->getAuthor().toLower().contains(lowerQuery) ||
                article->getLink().toLower().contains(lowerQuery))
            {
                results.push_back(item.get());
                continue;
            }
        }
    }

    return results;
}

void Library::importItems(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open import file:" << filePath;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull())
    {
        qDebug() << "Invalid JSON in import file";
        return;
    }

    // Get the directory of the import file to resolve relative paths
    QFileInfo fileInfo(filePath);
    QString importDir = fileInfo.absolutePath();

    QJsonArray jsonArray = doc.array();
    int importedCount = 0;

    for (const QJsonValue &value : jsonArray)
    {
        QJsonObject obj = value.toObject();
        QString type = obj["type"].toString();

        std::unique_ptr<Item> item;
        if (type == "book")
        {
            item = std::make_unique<Book>();
            static_cast<Book *>(item.get())->setAuthor(obj["author"].toString());
        }
        else if (type == "movie")
        {
            item = std::make_unique<Movie>();
            static_cast<Movie *>(item.get())->setDirector(obj["director"].toString());
        }
        else if (type == "article")
        {
            item = std::make_unique<Article>();
            static_cast<Article *>(item.get())->setLink(obj["link"].toString());
            static_cast<Article *>(item.get())->setAuthor(obj["author"].toString());
        }
        else
        {
            continue; // Skip invalid item types
        }

        // Set basic properties
        item->setTitle(obj["title"].toString());
        item->setDescription(obj["description"].toString());
        item->setYear(obj["year"].toInt());
        item->setReview(obj["review"].toInt());
        item->setComment(obj["comment"].toString());

        // Handle image
        if (obj.contains("imagePath") && !obj["imagePath"].isNull())
        {
            QString imagePath = obj["imagePath"].toString();
            // Resolve the relative path against the import file's directory
            QString absoluteImagePath = QDir(importDir).absoluteFilePath(imagePath);

            if (QFile::exists(absoluteImagePath))
            {
                QString newImagePath = copyImageToDb(absoluteImagePath, item->getId());
                if (!newImagePath.isEmpty())
                {
                    item->setImagePath(newImagePath);
                }
                else
                {
                    item->setImagePath(getDefaultImagePath(item.get()));
                }
            }
            else
            {
                item->setImagePath(getDefaultImagePath(item.get()));
            }
        }
        else
        {
            item->setImagePath(getDefaultImagePath(item.get()));
        }

        items.push_back(std::move(item));
        importedCount++;
    }

    saveToFile();
    qDebug() << "Imported" << importedCount << "items from" << filePath;
}

void Library::exportItems(const QString &dirPath)
{
    // Create export directory if it doesn't exist
    QDir dir(dirPath);
    if (!dir.exists() && !dir.mkpath("."))
    {
        qDebug() << "Failed to create export directory:" << dirPath;
        return;
    }

    // Create images subdirectory
    QDir imagesDir(dirPath + "/images");
    if (!imagesDir.exists() && !imagesDir.mkpath("."))
    {
        qDebug() << "Failed to create images directory";
        return;
    }

    QJsonArray jsonArray;
    JSONVisitor jsonVisitor;

    for (const auto &item : items)
    {
        item->accept(jsonVisitor);
        QJsonObject obj = jsonVisitor.getResult();

        // Handle image path
        QString currentImagePath = item->getImagePath();
        if (!currentImagePath.isEmpty() && QFile::exists(currentImagePath))
        {
            // Copy image to export directory
            QString fileName = QFileInfo(currentImagePath).fileName();
            QString newImagePath = imagesDir.filePath(fileName);
            if (QFile::copy(currentImagePath, newImagePath))
            {
                // Update image path to be relative to images directory
                obj["imagePath"] = "images/" + fileName;
            }
            else
            {
                obj["imagePath"] = QString();
            }
        }
        else
        {
            obj["imagePath"] = QString();
        }

        jsonArray.append(obj);
    }

    // Save JSON file
    QJsonDocument doc(jsonArray);
    QFile file(dir.filePath("data.json"));
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to create export file";
        return;
    }

    file.write(doc.toJson());
    qDebug() << "Exported" << items.size() << "items to" << dirPath;
}