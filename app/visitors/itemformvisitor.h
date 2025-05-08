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

class ItemFormVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit ItemFormVisitor(QObject *parent = nullptr, Item *item = nullptr);
    ~ItemFormVisitor() override = default;
    QWidget *getResult() const { return form; }

    // Keep the parameters to allow future "edit item" functionality
    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

signals:
    void createItemRequested(Item *item);
    void updateItemRequested(Item *item);

private slots:
    void onCreateButtonClicked();
    void onUpdateButtonClicked();

private:
    enum class FormType
    {
        Book,
        Movie,
        Article
    };

    void populateFormFields(Item *item);
    Item *createItemFromForm() const;

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

    // Currently edited item
    // Set to nullptr if creating a new item
    Item *item;

    // If true, the visitor is in edit mode
    bool isEditing;
};

#endif // ITEMFORMVISITOR_H