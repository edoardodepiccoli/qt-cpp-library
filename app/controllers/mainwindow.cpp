#include "mainwindow.h"
#include "../views/indexview.h"
#include "../views/newitemview.h"
#include "../views/edititemview.h"
#include "../views/showitemview.h"

#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QUuid>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      stackedWidget(new QStackedWidget),
      indexView(new IndexView),
      newItemView(new NewItemView),
      editItemView(new EditItemView),
      showItemView(new ShowItemView),
      libraryModel(std::make_unique<Library>())
{
    resize(800, 600);

    setupViews();
    connectSignals();

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(stackedWidget);
    central->setLayout(layout);

    setCentralWidget(central);

    QToolBar *toolbar = addToolBar("Navigation");
    QAction *indexAction = toolbar->addAction("Index");
    QAction *newItemAction = toolbar->addAction("New Item");

    connect(indexAction, &QAction::triggered, this, [this]()
            { stackedWidget->setCurrentWidget(indexView); });
    connect(newItemAction, &QAction::triggered, this, [this]()
            { stackedWidget->setCurrentWidget(newItemView); });

    stackedWidget->setCurrentWidget(indexView);
    indexView->populateFromLibrary(libraryModel.get());
}

void MainWindow::setupViews()
{
    indexView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    newItemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    editItemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    showItemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    stackedWidget->addWidget(indexView);
    stackedWidget->addWidget(newItemView);
    stackedWidget->addWidget(editItemView);
    stackedWidget->addWidget(showItemView);
}

void MainWindow::connectSignals()
{
    connect(newItemView, &NewItemView::createItemRequested, this, &MainWindow::handleCreateItemRequest);

    connect(indexView, &IndexView::itemShowRequested, this, &MainWindow::handleShowItemRequest);
}

void MainWindow::handleCreateItemRequest(Item *item)
{
    libraryModel->addItem(std::unique_ptr<Item>(item));
    indexView->populateFromLibrary(libraryModel.get());
    stackedWidget->setCurrentWidget(indexView);
}

void MainWindow::handleShowItemRequest(const QUuid &itemId)
{
    Item *item = libraryModel->getItem(itemId);
    ShowItemView *showItemView = new ShowItemView(this, item);

    connect(showItemView, &ShowItemView::deleteItemRequested, this, &MainWindow::handleDeleteItemRequest);
    connect(showItemView, &ShowItemView::editItemRequested, this, &MainWindow::handleEditItemRequest);

    stackedWidget->addWidget(showItemView);
    stackedWidget->setCurrentWidget(showItemView);
}

void MainWindow::handleEditItemRequest(const QUuid &itemId)
{
    Item *item = libraryModel->getItem(itemId);
    EditItemView *editItemView = new EditItemView(this, item);
    stackedWidget->addWidget(editItemView);
    stackedWidget->setCurrentWidget(editItemView);
}

void MainWindow::handleDeleteItemRequest(const QUuid &itemId)
{
    libraryModel->removeItem(itemId);
    indexView->populateFromLibrary(libraryModel.get());
    stackedWidget->setCurrentWidget(indexView);
}