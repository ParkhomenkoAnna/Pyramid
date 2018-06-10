#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <openfile.h>
#include <QPixmap>
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
    QLineEdit *rateEdit;
    Painter *painter;
    QList <QPixmap> imageList;
    int current;

private:
    Ui::MainWindow *ui;

    void createMenu();
    void setupWidgets();
    void setImage(QPixmap);
    void creatingLayer(QPixmap);

private slots:
    void setRate();
    void openImages();
    void showLayer(int);
    void showImage(int);
};

#endif // MAINWINDOW_H
