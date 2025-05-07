#pragma once
#include <QWidget>
#include <QUuid>

class QVBoxLayout;
class Library;

class IndexView : public QWidget
{
    Q_OBJECT

public:
    explicit IndexView(QWidget *parent = nullptr);
    void populateFromLibrary(Library *library);

signals:
    void deleteItemRequested(const QUuid &itemId);
    void viewItemRequested(const QUuid &itemId);

private:
    QVBoxLayout *mainLayout;
    Library *libraryModel;
};
