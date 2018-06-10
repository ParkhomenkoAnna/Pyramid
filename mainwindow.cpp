#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QScrollArea>
#include <openfile.h>
#include <QDebug>
#include <QList>
#include <math.h>
#include <QWidget>
#include <QLineEdit>

//сортировка списка изображений
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
    setupWidgets();

    this->setMinimumSize(580,600);
    this->setWindowTitle("Pyramid");

    //Слоты для выбора слоев/изображений из списка; Установка коэффициента уменьшения
    connect(imageLayerBox, SIGNAL(activated(int)), this, SLOT(showLayer(int)));
    connect(imageListBox, SIGNAL(activated(int)), this, SLOT(showImage(int)));
    connect(rateEdit, SIGNAL(returnPressed()), this, SLOT(setRate()));
}


void MainWindow::setupWidgets()
{
    QVBoxLayout * vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;

    imageLayerBox = new QComboBox;
    imageListBox = new QComboBox;

    painter = new Painter();
    painter->repaint();

    QScrollArea * scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(painter);

    rateEdit = new QLineEdit();
    rateEdit->setFixedSize(100,20);
    rateEdit->setToolTip("From 1.5 to 100");
    rateEdit->setText("Rate");

    hlayout->addWidget(imageListBox);
    hlayout->addWidget(imageLayerBox);
    hlayout->addWidget(rateEdit);

    vlayout->addLayout(hlayout);
    vlayout->addWidget(scrollArea);
    ui->centralWidget->setLayout(vlayout);
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
        imageList.append(QPixmap(lst.at(i)));

    imageListBox->addItems(lst);
    imageListBox->show();

    this->setWindowTitle("Pyramid - " + lst.first());
    current = 0;
    setImage(imageList.at(current));
}

void MainWindow::setImage( QPixmap pixmap)
{
    painter->pixmap = pixmap;
    painter->size = pixmap.size();
    painter->repaint();

    // Очистка QComboBox от предыдущих значений
    imageLayerBox->clear();

    // Построение пирамиды изображений
    creatingLayer(pixmap);
}

void MainWindow::creatingLayer(QPixmap pixmap)
{
    QStringList sizeList;
    QSize size = pixmap.size();
    do
    {
        sizeList.append("Layer "+QString::number(sizeList.length()).toUtf8()+": "+QString::number(size.height()).toUtf8()+"x"+QString::number(size.width()).toUtf8());
        size  /= rate;
    }
    while (size.width() > 1 || size.height() > 1);
    imageLayerBox->addItems(sizeList);
    imageLayerBox->show();
}

void MainWindow::showLayer(int index)
{
    QPixmap pixmap(imageList.at(current));
    painter->pixmap = pixmap.scaled(imageList.at(current).size()/(pow(rate,index)));
    painter->size = imageList.at(current).size();

    painter->repaint();
}

void MainWindow::showImage(int index)
{
    current = index;
    setImage(imageList.at(current));
}

void MainWindow::setRate()
{
    //валидация полученного значения
    QRegExp exp("([0-9\\.]*[0-9])+");
    if (exp.exactMatch(rateEdit->text()) && rateEdit->text().toDouble() > 1.5 && rateEdit->text().toDouble() < 100)
    {
        // установка полученного коэффициента и перерасчет слоев
        rate = rateEdit->text().toDouble();
        if (!imageList.isEmpty())
            setImage(imageList.at(current));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
