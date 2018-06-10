#include "painter.h"
#include <QPainter>
#include <QPixmap>

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
      size = QSize(500,500);
      pixmap = QPixmap(size);
      pixmap.fill(Qt::white);
      setMinimumSize(size);
}

Painter::~Painter()
{
}

void Painter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    this->setFixedSize(size);
    painter.drawPixmap(0,0, pixmap.scaled(size));
    painter.end();
}


