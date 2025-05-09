#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include "../models/item.h"
#include "../visitors/itemformvisitor.h"

class NewItemView : public QWidget
{
    Q_OBJECT
public:
    explicit NewItemView(QWidget *parent = nullptr);
    ~NewItemView() override = default;

    void setUpForm(const QString &type);
    ItemFormVisitor *getCurrentFormVisitor() const { return currentFormVisitor; }

signals:
    void createItemRequested(Item *item);

private:
    QVBoxLayout *mainLayout;
    QComboBox *typeComboBox;
    QWidget *currentForm = nullptr;
    QString currentImagePath;
    ItemFormVisitor *currentFormVisitor = nullptr;

private slots:
    void onTypeChanged(const QString &type);
};
