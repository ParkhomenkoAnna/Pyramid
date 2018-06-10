#include "painter.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>

using namespace std;

class QPaintEvent;

#include <QPixmap>

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
}

Painter::~Painter()
{
}

void Painter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!pixmap.isNull())
    {
        painter.drawPixmap(0,0, pixmap);
        this->setFixedSize(pixmap.width(), pixmap.height());
    }
    else
    {
     //   pixmap.scaled(500,500);
        painter.drawRect(0,0,500,500);
        painter.fillRect(0,0,500,500,QBrush(Qt::white));
    }
}


