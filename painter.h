#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
class QPaintEvent;
class QWheelEvent;



class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = 0);
   ~Painter();
    QPixmap  pixmap;


private:
protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // PAINTER_H
