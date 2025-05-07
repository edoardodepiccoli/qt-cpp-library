#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>

class NewItemView : public QWidget
{
    Q_OBJECT
public:
    explicit NewItemView(QWidget *parent = nullptr);

    void setUpForm(const QString &type);

private:
    QVBoxLayout *mainLayout;
    QComboBox *typeComboBox;
    QWidget *currentForm;

private slots:
    void onTypeChanged(const QString &type);
};
