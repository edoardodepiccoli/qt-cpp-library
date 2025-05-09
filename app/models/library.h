#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include <QUuid>
#include <QString>
#include <QTextStream>
#include "item.h"
#include "book.h"
#include "movie.h"
#include "article.h"

class Library
{
public:
    Library();
    ~Library() = default;

    void addItem(std::unique_ptr<Item> item);
    void removeItem(const QUuid &id);
    void removeItem(int index); // Keep old version for compatibility with the CLI stuff (should probably remove this)
    Item *getItem(const QUuid &id) const;
    Item *getItem(int index) const; // Keep old version
    int getItemCount() const;
    const std::vector<std::unique_ptr<Item>> &getItems() const { return items; }
    bool updateItem(const QUuid &id, std::unique_ptr<Item> newItem);
    std::vector<Item *> searchItems(const QString &query) const;

    bool saveToFile();
    bool loadFromFile();

    void accept(Visitor &visitor);

    // Image management methods
    QString setItemImage(const QUuid &id, const QString &sourceImagePath);
    QString getDefaultImagePath(const Item *item) const;
    void removeItemImage(const QUuid &id);

private:
    std::vector<std::unique_ptr<Item>> items;
    QString copyImageToDb(const QString &sourcePath, const QUuid &itemId);
    void ensureImagesDirectoryExists();
    QTextStream out{stdout};
};

#endif // LIBRARY_H