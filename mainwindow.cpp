#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <openfile.h>
#include <QDebug>
#include <QComboBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    rate = 2;
    setWindowTitle("Image Viewer");
    ui->setupUi(this);

    createMenu();

    imgLayer = new QComboBox;
    imgLayer->hide();

    QVBoxLayout * vlayout = new QVBoxLayout;


    QScrollArea * scrollArea = new QScrollArea;
    painter = new Painter();
    painter->setMinimumSize(500,500);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(painter);

    vlayout->addWidget(imgLayer);
    vlayout->addWidget(scrollArea);
    ui->centralWidget->setLayout(vlayout);

    this->setMinimumSize(580,600);
    this->setWindowTitle("Pyramid");

    connect(imgLayer, SIGNAL(activated(int)), this, SLOT(show_layer(int)));
}

void MainWindow::createMenu()
{
    QMenu *menu = new QMenu("&File");
    QAction *openImg = new QAction("Open image", menu);
    menu->addAction(openImg);
    ui->menuBar->addMenu(menu);
    connect(openImg, SIGNAL(triggered()), this, SLOT(open()));
}

void MainWindow::show_layer(int index)
{
   painter->pixmap = pixmapList.at(index);
   painter->update();
}


void MainWindow::open()
{
    OpenFile open;
    open.setWindowFlags(Qt::WindowFullscreenButtonHint);
    open.exec();
    if (!open.fname.isEmpty() && !open.fpath.isEmpty())
    {
       setImage( open.fpath, open.fname);
    }
}

void MainWindow::setImage(QString path, QString name)
{
    this->setWindowTitle("Pyramid - " + name);
    QPixmap pixmap(path+name);
    painter->pixmap = pixmap;

    // очистка списка Pixmap от предыдущих изображений и очистка виджета QComboBox
    imgLayer->clear();
    pixmapList.clear();

    // построение новой пирамиды изображений
    creatingPyramid(pixmap);
}


void MainWindow::creatingPyramid(QPixmap pixmap)
{
    QStringList sizeList;
    QSize size = pixmap.size();
    do
    {
        pixmapList.append(pixmap.scaled(size));
        sizeList.append(QString::number(size.height()).toUtf8()+"x"+QString::number(size.width()).toUtf8());
        size  /= 2;
    }
    while (size.width() > 1 || size.height() > 1);
    imgLayer->addItems(sizeList);
    imgLayer->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
