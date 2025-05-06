#include "indexview.h"
#include <QVBoxLayout>
#include <QLabel>

IndexView::IndexView(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("This is IndexView"));
    layout->addStretch();

    setLayout(layout);
}
