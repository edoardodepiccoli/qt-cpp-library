#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include <QUuid>
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

private:
    std::vector<std::unique_ptr<Item>> items;
    // Removed the lookup map because I thought it was cool but it was completely unnecessary (duh)
};

#endif // LIBRARY_H