#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <openfile.h>
#include <painter.h>
#include <about.h>

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QComboBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <openfile.h>
#include <QDebug>
#include <QList>
#include <math.h>
#include <QLineEdit>

#include <QCommandLineParser>
#include <QCommandLineOption>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QStringList, QWidget *parent = 0);
    ~MainWindow();
    float rate;
    QComboBox * imageLayerBox, *imageListBox;
    QLineEdit *rateEdit;
    Painter *painter;
    QList <QPixmap> imageList;
    int current;

private:
    Ui::MainWindow *ui;

    void setupMenu();
    void setupWidgets();
    void setupOptions(QStringList );

    void setImage(QPixmap);
    void creatingLayer(QPixmap);

private slots:

    void about();
    void setRate();
    void getImages();
    void openImages(QStringList);
    void showLayer(int);
    void showImage(int);
};

#endif // MAINWINDOW_H
