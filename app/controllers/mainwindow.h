#include <QMainWindow>
#include <QStackedWidget>
#include <QUuid>

#include "../models/library.h"

class IndexView;
class ShowItemView;
class NewItemView;
class EditItemView;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void handleDeleteItemRequest(const QUuid &itemId);

private:
    QStackedWidget *stackedWidget;

    IndexView *indexView;
    ShowItemView *showItemView;
    NewItemView *newItemView;
    EditItemView *editItemView;

    std::unique_ptr<Library> libraryModel;

    void setupViews();
    void connectSignals();
};
