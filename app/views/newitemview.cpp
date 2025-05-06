#include "newitemview.h"
#include <QVBoxLayout>
#include <QLabel>

NewItemView::NewItemView(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("This is NewItemView"));
    layout->addStretch();

    setLayout(layout);
}
