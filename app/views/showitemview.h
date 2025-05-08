#include <QWidget>
#include <QVBoxLayout>
#include <memory>

#include "../models/item.h"

class ShowItemView : public QWidget
{
    Q_OBJECT

public:
    ShowItemView(QWidget *parent = nullptr, Item *item = nullptr);
    ~ShowItemView();

signals:
    void deleteItemRequested(const QUuid &itemId);
    void editItemRequested(const QUuid &itemId);

private:
    std::unique_ptr<Item> item; // Take ownership of the item
    QVBoxLayout *layout;
};