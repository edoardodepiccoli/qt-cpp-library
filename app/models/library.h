#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include <QMap>
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
    void removeItem(const QUuid &id);     // Changed to use ID
    void removeItem(int index);           // Keep old version for compatibility if needed
    Item *getItem(const QUuid &id) const; // New ID-based lookup
    Item *getItem(int index) const;       // Keep old version
    int getItemCount() const;
    const std::vector<std::unique_ptr<Item>> &getItems() const { return items; }

    bool saveToFile();
    bool loadFromFile();

    void accept(Visitor &visitor);

private:
    std::vector<std::unique_ptr<Item>> items;
    QMap<QUuid, Item *> idToItemMap; // New mapping for quick lookup (idk if this is necessary but it seemed cool to use lmao)
};

#endif // LIBRARY_H