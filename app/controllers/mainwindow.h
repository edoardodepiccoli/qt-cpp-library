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
    ~MainWindow() override = default;

private slots:
    void handleCreateItemRequest(Item *item);

    void handleShowItemRequest(const QUuid &itemId);

    void handleEditItemRequest(const QUuid &itemId);
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
