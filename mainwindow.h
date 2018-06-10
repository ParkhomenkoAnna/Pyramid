#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <openfile.h>
#include <QPixmap>
#include <QLabel>
#include <QComboBox>
#include <painter.h>

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
    float rate;
    QComboBox * imgLayer;
    Painter *painter;
    QList <QPixmap> pixmapList;

private:
    Ui::MainWindow *ui;
    void createMenu();
    void setImage(QString, QString);

    void creatingPyramid(QPixmap );

private slots:
    void open();
    void show_layer(int);
};

#endif // MAINWINDOW_H
