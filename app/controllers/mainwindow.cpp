#include "mainwindow.h"
#include "../views/indexview.h"
#include "../views/newitemview.h"
#include "../views/edititemview.h"
#include "../views/showitemview.h"

#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>

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
    // Set different styles to test view change
    // indexView->setStyleSheet("background-color: gray;");
    // newItemView->setStyleSheet("background-color: black;");
    // editItemView->setStyleSheet("background-color: darkred;");
    // showItemView->setStyleSheet("background-color: darkblue;");

    // Force them to expand and fill the stacked widget
    indexView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    newItemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    editItemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    showItemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Put them into the QStackedWidget
    stackedWidget->addWidget(indexView);
    stackedWidget->addWidget(newItemView);
    stackedWidget->addWidget(editItemView);
    stackedWidget->addWidget(showItemView);
}

void MainWindow::connectSignals()
{
}
