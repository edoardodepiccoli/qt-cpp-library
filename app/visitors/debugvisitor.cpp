#include "debugvisitor.h"
#include <QDebug>

void DebugVisitor::visit(Book& book) {
    qDebug() << "Book:";
    qDebug() << "  Title:" << book.getTitle();
    qDebug() << "  Description:" << book.getDescription();
    qDebug() << "  Year:" << book.getYear();
    qDebug() << "  Review:" << book.getReview();
    qDebug() << "  Comment:" << book.getComment();
    qDebug() << "  Author:" << book.getAuthor();
    qDebug() << "";
}

void DebugVisitor::visit(Movie& movie) {
    qDebug() << "Movie:";
    qDebug() << "  Title:" << movie.getTitle();
    qDebug() << "  Description:" << movie.getDescription();
    qDebug() << "  Year:" << movie.getYear();
    qDebug() << "  Review:" << movie.getReview();
    qDebug() << "  Comment:" << movie.getComment();
    qDebug() << "  Director:" << movie.getDirector();
    qDebug() << "";
}

void DebugVisitor::visit(Article& article) {
    qDebug() << "Article:";
    qDebug() << "  Title:" << article.getTitle();
    qDebug() << "  Description:" << article.getDescription();
    qDebug() << "  Year:" << article.getYear();
    qDebug() << "  Review:" << article.getReview();
    qDebug() << "  Comment:" << article.getComment();
    qDebug() << "  Link:" << article.getLink();
    qDebug() << "";
} 