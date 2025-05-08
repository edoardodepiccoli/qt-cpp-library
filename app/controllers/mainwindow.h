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

    void clearCurrentView();

signals:
    void navigateToIndex();
    void navigateToNewItem();
    void navigateToEditItem(Item *item);
    void navigateToShowItem(Item *item);

private slots:
    // CRUD slots
    void handleCreateItemRequest(Item *item);
    void handleShowItemRequest(const QUuid &itemId);
    void handleEditItemRequest(const QUuid &itemId);
    void handleDeleteItemRequest(const QUuid &itemId);

    // Navigation slots
    void setIndexView();
    void setNewItemView();
    void setEditItemView(Item *item);
    void setShowItemView(Item *item);

private:
    QStackedWidget *stackedWidget;
    std::unique_ptr<Library> libraryModel;
};
