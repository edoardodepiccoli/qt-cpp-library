#pragma once
#include <QWidget>
#include <QVBoxLayout>

#include "../models/item.h"

class EditItemView : public QWidget
{
    Q_OBJECT
public:
    explicit EditItemView(QWidget *parent = nullptr, Item *item = nullptr);
    ~EditItemView() override = default;

signals:
    void updateItemRequested(Item *item);

private:
    Item *item;
    QVBoxLayout *layout;
};
