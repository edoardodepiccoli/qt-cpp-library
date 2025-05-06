#include <QMainWindow>
#include <QStackedWidget>

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

private:
    QStackedWidget *stackedWidget; // Switches between views

    // Main views
    IndexView *indexView;
    ShowItemView *showItemView;
    NewItemView *newItemView;
    EditItemView *editItemView;

    std::unique_ptr<Library> libraryModel; // Owns the data

    void setupViews();
    void connectSignals();
};