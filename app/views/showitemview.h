#include <QWidget>
#include <QVBoxLayout>
#include <memory>

#include "../models/item.h"
#include "../visitors/itemshowvisitor.h"

class ShowItemView : public QWidget
{
    Q_OBJECT

public:
    explicit ShowItemView(QWidget *parent, Item *item);
    ~ShowItemView() = default;

signals:
    void deleteItemRequested(const QUuid &id);
    void editItemRequested(const QUuid &id);

private:
    Item *item; // Store a reference instead of taking ownership
    QVBoxLayout *layout;
    std::unique_ptr<ItemShowVisitor> visitor; // Own the visitor
};