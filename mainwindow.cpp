#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("Image Viewer");
    ui->setupUi(this);

    QScrollArea * scrollArea= new QScrollArea;
    QLabel * imageLabel = new QLabel;
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

QPixmap MainWindow::getPixmap()
{
    QPixmap pixmap(500,500);
    QPainter painter;
    painter.begin(&pixmap);
    painter.drawRect(0,0,500,500);
    painter.fillRect(0,0,500,500,QBrush(Qt::white));
    painter.end();
    return pixmap;
}

MainWindow::~MainWindow()
{
    delete ui;
}
