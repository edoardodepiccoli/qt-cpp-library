#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "library.h"
#include "../visitors/jsonvisitor.h"

Library::Library()
{
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
        items.erase(it);
        saveToFile();
    }
}

void Library::removeItem(int index)
{
    if (index >= 0 && index < static_cast<int>(items.size()))
    {
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

bool Library::saveToFile()
{
    QJsonArray jsonArray;
    JSONVisitor jsonVisitor;

    for (const auto &item : items)
    {
        item->accept(jsonVisitor);
        jsonArray.append(jsonVisitor.getResult());
    }

    QJsonDocument doc(jsonArray);
    QFile file("app/db/data.json");

    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file.write(doc.toJson());
    return true;
}

bool Library::loadFromFile()
{
    QFile file("app/db/data.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
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
        newItem->setId(id);
        *it = std::move(newItem);
        saveToFile();
        return true;
    }
    return false;
}

void Library::accept(Visitor &visitor)
{
    for (const auto &item : items)
    {
        item->accept(visitor);
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

        bool found = false;

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