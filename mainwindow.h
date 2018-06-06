#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <openfile.h>
#include <QPixmap>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString imagePath, imageName;
    QPixmap *pixmap;
    QLabel *imageLabel;

private:
    Ui::MainWindow *ui;
    void createMenus();
    QPixmap getPixmap();
    QPainter * painter;
    void setImage(QString path, QString name);


private slots:
    void open();
};

#endif // MAINWINDOW_H
