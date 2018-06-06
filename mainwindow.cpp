#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <openfile.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("Image Viewer");
    ui->setupUi(this);

    createMenus();
    QScrollArea * scrollArea= new QScrollArea;
    imageLabel = new QLabel;
    imageLabel->setMinimumSize(500,500);
    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(imageLabel);
    imageLabel->setPixmap(getPixmap());


    setCentralWidget(scrollArea);
    this->setMinimumSize(540,540);
    this->setWindowTitle("Pyramid");

}

void MainWindow::createMenus()
{
    QMenu *menu = new QMenu("&File");
    QAction *openImg = new QAction("Open image", menu);
    menu->addAction(openImg);
    ui->menuBar->addMenu(menu);
    connect(openImg, SIGNAL(triggered()), this, SLOT(open()));
}

QPixmap MainWindow::getPixmap()
{

    pixmap = new QPixmap(500,500);
    painter = new QPainter;
    painter->begin(pixmap);
    painter->drawRect(0,0,500,500);
    painter->fillRect(0,0,500,500,QBrush(Qt::white));
    painter->end();
    return *pixmap;
}

void MainWindow::open()
{
    OpenFile open;
    open.setWindowFlags(Qt::WindowFullscreenButtonHint);
    open.exec();
    if (!open.fname.isEmpty() && !open.fpath.isEmpty())
    {
       imagePath = open.fpath;
       imageName = open.fname;
       setImage(imagePath,imageName);
    }
}

void MainWindow::setImage(QString path, QString name)
{
    this->setWindowTitle("Pyramid - " + name);
    pixmap->load(path+name);
    imageLabel->resize(pixmap->size());
    imageLabel->setPixmap(*pixmap);
}


MainWindow::~MainWindow()
{
    delete ui;
}
