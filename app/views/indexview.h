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
    ~IndexView() override = default;

    void populateFromLibrary(Library *library);

signals:
    // Qt automatically forwards the parameters when the signatures match, cool stuff
    void itemShowRequested(const QUuid &itemId);

private:
    QVBoxLayout *mainLayout;
    Library *libraryModel;
};
