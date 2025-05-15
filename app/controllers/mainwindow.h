#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QUuid>

#include "../models/library.h"

class IndexView;
class ShowItemView;
class NewItemView;
class EditItemView;
class ItemFormVisitor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

    void clearCurrentView();

private slots:
    // CRUD slots
    void handleCreateItemRequest(Item *item);
    void handleShowItemRequest(const QUuid &itemId);
    void handleEditItemRequest(Item *item);
    void handleUpdateItemRequest(Item *item);
    void handleDeleteItemRequest(const QUuid &itemId);

    // Navigation slots
    void setIndexView();
    void setNewItemView();
    void setEditItemView(Item *item);
    void setShowItemView(Item *item);

    // Import/Export slots
    void handleImportItemsRequest();
    void handleExportItemsRequest();

private:
    QStackedWidget *stackedWidget;

    // These two go hand in hand, maybe they are too coupled together but for now it's fine
    std::unique_ptr<Library> libraryModel;
    QString currentSearchQuery;
    QString pendingImagePath; // Store the image path temporarily
};

#endif // MAINWINDOW_H
