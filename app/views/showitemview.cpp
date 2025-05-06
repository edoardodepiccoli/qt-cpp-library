#include "showitemview.h"
#include <QVBoxLayout>
#include <QLabel>

ShowItemView::ShowItemView(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("This is ShowItemView"));
    layout->addStretch();

    setLayout(layout);
}
