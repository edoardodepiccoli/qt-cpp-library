#include "mainwindow.h"
#include "../views/indexview.h"
#include "../views/newitemview.h"
#include "../views/edititemview.h"
#include "../views/showitemview.h"
#include "../visitors/itemformvisitor.h"

#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QUuid>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      stackedWidget(nullptr),
      libraryModel(std::make_unique<Library>())
{
    resize(800, 600);

    // Set up central widget
    QWidget *central = new QWidget(this);
    // Set up layout for the central widget
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create and parent the stacked widget to the central widget
    stackedWidget = new QStackedWidget(central);
    // Add stacked widget to layout
    layout->addWidget(stackedWidget);

    // Set up toolbar (Qt automatically places it at the top of the window)
    QToolBar *toolbar = addToolBar("Navigation");
    QAction *indexAction = toolbar->addAction("Index");
    QAction *newItemAction = toolbar->addAction("New Item");
    toolbar->addSeparator();
    QAction *importAction = toolbar->addAction("Import Items");
    QAction *exportAction = toolbar->addAction("Export Items");

    connect(indexAction, &QAction::triggered, this, &MainWindow::setIndexView);
    connect(newItemAction, &QAction::triggered, this, &MainWindow::setNewItemView);
    connect(importAction, &QAction::triggered, this, &MainWindow::handleImportItemsRequest);
    connect(exportAction, &QAction::triggered, this, &MainWindow::handleExportItemsRequest);

    // Set central widget
    setCentralWidget(central);

    // Set the IndexView as the initial view
    setIndexView();
}

void MainWindow::clearCurrentView()
{
    // Get the current widget
    QWidget *currentWidget = stackedWidget->currentWidget();
    // Only remove and delete if we have a valid widget
    // Fortunately, Qt automatically handles the deletion of an inexistent widget and does nothing, very handy
    if (currentWidget)
    {
        // Remove it from the stacked widget
        stackedWidget->removeWidget(currentWidget);
        // Delete it
        delete currentWidget;
    }
}

// Navigation slots
void MainWindow::setIndexView()
{
    // Clear the current view
    clearCurrentView();

    // Initialize the IndexView
    IndexView *indexView = new IndexView(this);
    indexView->populateFromLibrary(libraryModel.get(), currentSearchQuery);

    // Connect signals and slots
    connect(indexView, &IndexView::itemShowRequested, this, &MainWindow::handleShowItemRequest);

    // Place it in the stacked widget
    stackedWidget->addWidget(indexView);
    // Set it as the current view
    stackedWidget->setCurrentWidget(indexView);
}

void MainWindow::setNewItemView()
{
    // Clear the current view
    clearCurrentView();

    // Initialize the NewItemView
    NewItemView *newItemView = new NewItemView(this);

    // Connect signals and slots
    connect(newItemView, &NewItemView::createItemRequested, this, &MainWindow::handleCreateItemRequest);

    // Place it in the stacked widget
    stackedWidget->addWidget(newItemView);
    stackedWidget->setCurrentWidget(newItemView);
}

void MainWindow::setEditItemView(Item *item)
{
    // Clear the current view
    clearCurrentView();

    // Initialize the EditItemView
    EditItemView *editItemView = new EditItemView(this, item);

    // Connect signals and slots
    connect(editItemView, &EditItemView::updateItemRequested, this, &MainWindow::handleUpdateItemRequest);

    // Place it in the stacked widget
    stackedWidget->addWidget(editItemView);
    stackedWidget->setCurrentWidget(editItemView);
}

void MainWindow::setShowItemView(Item *item)
{
    // Clear the current view
    clearCurrentView();

    // Initialize the ShowItemView
    ShowItemView *showItemView = new ShowItemView(this, item);

    // Connect signals and slots
    connect(showItemView, &ShowItemView::deleteItemRequested, this, &MainWindow::handleDeleteItemRequest);

    // This is a lambda function that takes an itemId and sets the edit item view to the item with that id
    connect(showItemView, &ShowItemView::editItemRequested, this, [this](const QUuid &itemId)
            {
        // Get the item from the library
        Item *item = libraryModel->getItem(itemId);
        // Set the edit item view
        if (item) {
            setEditItemView(item);
        } });

    // Place it in the stacked widget
    stackedWidget->addWidget(showItemView);
    stackedWidget->setCurrentWidget(showItemView);
}

// CRUD slots
void MainWindow::handleCreateItemRequest(Item *item)
{
    libraryModel->addItem(std::unique_ptr<Item>(item));

    // Get the form visitor to check for pending image
    if (auto *newItemView = qobject_cast<NewItemView *>(stackedWidget->currentWidget()))
    {
        if (auto *formVisitor = newItemView->getCurrentFormVisitor())
        {
            QString imagePath = formVisitor->getCurrentImagePath();
            if (!imagePath.isEmpty())
            {
                libraryModel->setItemImage(item->getId(), imagePath);
            }
        }
    }

    setIndexView();
}

void MainWindow::handleShowItemRequest(const QUuid &itemId)
{
    // Get the item from the library
    Item *item = libraryModel->getItem(itemId);
    // Set the show item view
    setShowItemView(item);
}

void MainWindow::handleEditItemRequest(Item *item)
{
    if (libraryModel->updateItem(item->getId(), std::unique_ptr<Item>(item)))
    {
        setIndexView();
    }
}

void MainWindow::handleUpdateItemRequest(Item *item)
{
    if (libraryModel->updateItem(item->getId(), std::unique_ptr<Item>(item)))
    {
        // Get the form visitor to check for pending image
        if (auto *editItemView = qobject_cast<EditItemView *>(stackedWidget->currentWidget()))
        {
            if (auto *form = qobject_cast<ItemFormVisitor *>(editItemView->findChild<ItemFormVisitor *>()))
            {
                QString imagePath = form->getCurrentImagePath();
                if (!imagePath.isEmpty())
                {
                    libraryModel->setItemImage(item->getId(), imagePath);
                }
            }
        }

        setIndexView();
    }
}

void MainWindow::handleDeleteItemRequest(const QUuid &itemId)
{
    // Remove the item from the library
    libraryModel->removeItem(itemId);
    // Update the index view
    setIndexView();
}

void MainWindow::handleImportItemsRequest()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Import Items", "", "JSON Files (*.json)");

    if (!filePath.isEmpty())
    {
        libraryModel->importItems(filePath);
        // Refresh the current view to show imported items
        if (auto *indexView = qobject_cast<IndexView *>(stackedWidget->currentWidget()))
        {
            indexView->populateFromLibrary(libraryModel.get(), currentSearchQuery);
        }
        QMessageBox::information(this, "Import Complete", "Items have been imported successfully 😎");
    }
}

void MainWindow::handleExportItemsRequest()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,
                                                        "Export Items", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dirPath.isEmpty())
    {
        libraryModel->exportItems(dirPath);
        QMessageBox::information(this, "Export Complete", "Items have been exported successfully 😎");
    }
}