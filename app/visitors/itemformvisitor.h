#ifndef ITEMFORMVISITOR_H
#define ITEMFORMVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"
#include "../models/item.h"
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>

class ItemFormVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit ItemFormVisitor(QObject *parent = nullptr, Item *item = nullptr);
    ~ItemFormVisitor() override;
    QWidget *getResult() const { return form; }
    QString getCurrentImagePath() const { return currentImagePath; }

    // Keep the parameters to allow future "edit item" functionality
    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

    void setCurrentImagePath(const QString &path) { currentImagePath = path; }

signals:
    void createItemRequested(Item *item);
    void updateItemRequested(Item *item);
    void imagePathChanged(const QString &path);

private slots:
    void onCreateButtonClicked();
    void onUpdateButtonClicked();
    void onImageButtonClicked();

private:
    enum class FormType
    {
        Book,
        Movie,
        Article
    };

    void populateFormFields(Item *item);
    Item *createItemFromForm() const;
    void addImageUploadSection(QVBoxLayout *layout);

    QWidget *form;
    FormType currentFormType;

    // Form fields
    QLineEdit *titleEdit;
    QTextEdit *descriptionEdit;
    QLineEdit *yearEdit;
    QLineEdit *reviewEdit;
    QTextEdit *commentEdit;
    QLineEdit *authorEdit;
    QLineEdit *directorEdit;
    QLineEdit *linkEdit;
    QPushButton *imageButton;
    QLabel *imagePathLabel;
    QString currentImagePath;

    // Currently edited item
    // Set to nullptr if creating a new item
    Item *item;

    // If true, the visitor is in edit mode
    bool isEditing;
};

#endif // ITEMFORMVISITOR_H