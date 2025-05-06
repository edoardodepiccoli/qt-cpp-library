#include "edititemview.h"
#include <QVBoxLayout>
#include <QLabel>

EditItemView::EditItemView(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("This is EditItemView"));
    layout->addStretch();

    setLayout(layout);
}
