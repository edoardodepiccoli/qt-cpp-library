#pragma once
#include <QWidget>

class QVBoxLayout;
class Library;

class IndexView : public QWidget
{
    Q_OBJECT
public:
    explicit IndexView(QWidget *parent = nullptr);
    void populateFromLibrary(Library *library);

private:
    QVBoxLayout *mainLayout;
};
