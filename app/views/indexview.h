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

    void populateFromLibrary(Library *library, QString &searchQuery);

signals:
    // Qt automatically forwards the parameters when the signatures match, cool stuff
    void itemShowRequested(const QUuid &itemId);

private slots:
    void onSearchTextChanged(const QString &query);

private:
    QVBoxLayout *mainLayout;

    // These two go hand in hand, maybe they are too coupled together but for now it's fine
    Library *libraryModel;
    QString currentSearchQuery;

    QList<ItemCardVisitor *> visitors;
};
