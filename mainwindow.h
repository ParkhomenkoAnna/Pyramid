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
    float rate;
    QComboBox * imageLayerBox, *imageListBox;
    Painter *painter;
    QList <QPixmap> layerList, imageList;

private:
    Ui::MainWindow *ui;
    void createMenu();
    void setImage(QPixmap);
    void creatingPyramid(QPixmap );

private slots:
    void openImages();
    void showLayer(int);
    void showImage(int);
};

#endif // MAINWINDOW_H
