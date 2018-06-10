#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <openfile.h>
#include <QDebug>
#include <QComboBox>
#include <QList>
#include <math.h>

template<typename T> bool sortImages (const QString& x, const QString& y)
{
    //Расчет диагонали
    QPixmap tmp1(x), tmp2(y);
    double diagonal1 = sqrt(pow(tmp1.height(),2) + pow(tmp1.width(),2));
    double diagonal2 = sqrt(pow(tmp2.height(),2) + pow(tmp2.width(),2));
    return ( sqrt(diagonal1) < sqrt (diagonal2));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    rate = 2;
    setWindowTitle("Image Viewer");
    ui->setupUi(this);

    createMenu();

    imageLayerBox = new QComboBox;
    imageListBox = new QComboBox;
    imageLayerBox->hide();
    imageListBox->hide();

    QVBoxLayout * vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;

    QScrollArea * scrollArea = new QScrollArea;
    painter = new Painter();
    painter->repaint();

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(painter);

    hlayout->addWidget(imageListBox);
    hlayout->addWidget(imageLayerBox);

    vlayout->addLayout(hlayout);
    vlayout->addWidget(scrollArea);
    ui->centralWidget->setLayout(vlayout);

    this->setMinimumSize(580,600);
    this->setWindowTitle("Pyramid");

    connect(imageLayerBox, SIGNAL(activated(int)), this, SLOT(showLayer(int)));
    connect(imageListBox, SIGNAL(activated(int)), this, SLOT(showImage(int)));
}

void MainWindow::createMenu()
{
    QMenu *menu = new QMenu("&File");
    QAction *openImg = new QAction("Open image", menu);
    menu->addAction(openImg);
    ui->menuBar->addMenu(menu);
    connect(openImg, SIGNAL(triggered()), this, SLOT(openImages()));
}

void MainWindow::openImages()
{
    OpenFile open;
    open.setWindowFlags(Qt::WindowFullscreenButtonHint);
    open.exec();

   // Очистка списков Pixmap и виджетов QComboBox от предыдущих значений
    imageListBox->clear();
    imageList.clear();

    QStringList lst = open.imageList;
    qSort(lst.begin(), lst.end(), sortImages<QString>);
    for (int i=0; i< lst.length(); i++)
    {
        imageList.append(QPixmap(lst.at(i)));
    }
    imageListBox->addItems(lst);
    imageListBox->show();

    this->setWindowTitle("Pyramid - " + lst.first());
    setImage(imageList.first());
}

void MainWindow::setImage( QPixmap pixmap)
{
    painter->pixmap = pixmap;
    painter->size = pixmap.size();
    painter->repaint();

    // Очистка списков Pixmap и виджетов QComboBox от предыдущих значений
    imageLayerBox->clear();
    layerList.clear();

    // Построение пирамиды изображений
    creatingPyramid(pixmap);
}

void MainWindow::creatingPyramid(QPixmap pixmap)
{
    QStringList sizeList;
    QSize size = pixmap.size();
    do
    {
        layerList.append(pixmap.scaled(size));
        sizeList.append("Layer "+QString::number(layerList.length()).toUtf8()+": "+QString::number(size.height()).toUtf8()+"x"+QString::number(size.width()).toUtf8());
        size  /= 2;
    }
    while (size.width() > 1 || size.height() > 1);
    imageLayerBox->addItems(sizeList);
    imageLayerBox->show();
}

void MainWindow::showLayer(int index)
{
   painter->pixmap = layerList.at(index);
   painter->size = layerList.first().size();
   painter->repaint();
}

void MainWindow::showImage(int index)
{
    setImage(imageList.at(index));
}

MainWindow::~MainWindow()
{
    delete ui;
}

