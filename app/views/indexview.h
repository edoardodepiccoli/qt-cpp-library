#pragma once
#include <QWidget>
#include <QUuid>
#include <QList>

class QVBoxLayout;
class Library;
class ItemCardVisitor;

class IndexView : public QWidget
{
    Q_OBJECT

public:
    explicit IndexView(QWidget *parent = nullptr);
    ~IndexView() override;

    void populateFromLibrary(Library *library);

signals:
    // Qt automatically forwards the parameters when the signatures match, cool stuff
    void itemShowRequested(const QUuid &itemId);

private:
    QVBoxLayout *mainLayout;
    Library *libraryModel;
    QList<ItemCardVisitor *> visitors;
};
