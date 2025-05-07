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

    connect(indexAction, &QAction::triggered, this, [=]()
            { stackedWidget->setCurrentWidget(indexView); });
    connect(newItemAction, &QAction::triggered, this, [=]()
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
    connect(indexView, &IndexView::deleteItemRequested, this, &MainWindow::handleDeleteItemRequest);
}

void MainWindow::handleDeleteItemRequest(const QUuid &itemId)
{
    libraryModel->removeItem(itemId);
    indexView->populateFromLibrary(libraryModel.get());
}
