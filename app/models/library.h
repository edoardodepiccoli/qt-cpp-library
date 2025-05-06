#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include "item.h"
#include "book.h"
#include "movie.h"
#include "article.h"

class Library
{
public:
    Library();

    void addItem(std::unique_ptr<Item> item);
    void removeItem(int index);
    Item *getItem(int index) const;
    int getItemCount() const;
    const std::vector<std::unique_ptr<Item>> &getItems() const { return items; }

    bool saveToFile();
    bool loadFromFile();

    void accept(Visitor &visitor);

private:
    std::vector<std::unique_ptr<Item>> items;
};

#endif // LIBRARY_H