#ifndef ITEMCARDVISITOR_H
#define ITEMCARDVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"

#include <QWidget>
#include <QUuid>
#include <QObject>

class ItemCardVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit ItemCardVisitor(QObject *parent = nullptr);

    QWidget *getResult() const { return widget; }
    QUuid getItemId() const { return itemId; }

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

signals:
    void deleteItemRequested(const QUuid &itemId); // Signal to IndexView
    void viewItemRequested(const QUuid &itemId);   // Signal to IndexView

private slots:
    void onDeleteButtonClicked(); // New slot to handle button click
    void onViewButtonClicked();   // New slot to handle button click

private:
    QWidget *widget = nullptr;
    QUuid itemId; // Store the ID of the item this visitor is for
};

#endif // ITEMCARDVISITOR_H
