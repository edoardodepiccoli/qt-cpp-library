#include "library.h"
#include "../visitors/jsonvisitor.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Library::Library()
{
    loadFromFile();
}

void Library::addItem(std::unique_ptr<Item> item)
{
    items.push_back(std::move(item));
    saveToFile();
}

void Library::removeItem(int index)
{
    if (index >= 0 && index < static_cast<int>(items.size()))
    {
        items.erase(items.begin() + index);
        saveToFile();
    }
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
        }

        if (item)
        {
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

void Library::accept(Visitor &visitor)
{
    for (const auto &item : items)
    {
        item->accept(visitor);
    }
}