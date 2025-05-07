#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include "../models/item.h"
class NewItemView : public QWidget
{
    Q_OBJECT
public:
    explicit NewItemView(QWidget *parent = nullptr);

    void setUpForm(const QString &type);

signals:
    void createItemRequest(Item *item);

private:
    QVBoxLayout *mainLayout;
    QComboBox *typeComboBox;
    QWidget *currentForm;

private slots:
    void onTypeChanged(const QString &type);
    void onItemCreationRequest(Item *item);
};
