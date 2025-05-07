#ifndef ITEMFORMVISITOR_H
#define ITEMFORMVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"

#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

class ItemFormVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit ItemFormVisitor(QObject *parent = nullptr);

    QWidget *getResult() const { return form; }

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

signals:
    // The receiver (NewItemView) takes ownership of the item pointer, I think
    void createItemRequest(Item *item);

private slots:
    void onCreateButtonClicked();

private:
    enum class FormType
    {
        Book,
        Movie,
        Article
    };

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
};

#endif // ITEMFORMVISITOR_H