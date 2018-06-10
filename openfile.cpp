#include "openfile.h"
#include "ui_openfile.h"
#include <QWidget>
#include <QDialog>
#include <QFileSystemModel>
#include <QDebug>

OpenFile::OpenFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFile)
{
    ui->setupUi(this);
    this->setWindowTitle("Open image");
    lDir = new QFileSystemModel(this);
    lDir->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    lDir->setRootPath("~/");
    ui->listView->setModel(lDir);
    QModelIndex idx = lDir->index("~/");
    ui->listView->setRootIndex(idx);
    ui->widget->hide();

    masterTree = new QTreeView();
    connect(masterTree, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));
}

OpenFile::~OpenFile()
{
    delete ui;
}

void OpenFile::on_listView_clicked(const QModelIndex &index)
{
    fname = lDir->filePath(index);
    tDir = new QFileSystemModel(this);
    tDir->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    tDir->setRootPath(fname);
    QModelIndex idx1 = tDir->index(fname);
    masterTree->setModel(tDir);
    masterTree->setRootIndex(idx1);
    ui->horizontalLayout->addWidget(masterTree);
}

void OpenFile::addedNewTree(QFileSystemModel * tDir, const QModelIndex index)
{
    newTree = new QTreeView(this);
    newTree->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->horizontalLayout->addWidget(newTree,100);
    newTree->setModel(tDir);
    newTree->setRootIndex(index);
    connect(newTree, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));
}

void OpenFile::on_clicked(const QModelIndex &index)
{
    QRegExp exp("([a-zA-Z0-9_ \\#\\:\\-\\.\\C\\)\\+ ])+\\.(JPG|png|jpg|gif|jpeg)");
    dir = new QDir();
    tDir->filePath(index);
    QString name = tDir->fileInfo(index).fileName();
    if (tDir->isDir(index))
    {
        addedNewTree(tDir, index);
    }
    if (exp.exactMatch(name))
    {
        ui->widget->show();
        fname = name;
        fpath=tDir->filePath(index).remove(fname);
        ui->imgName->setText(name);
        int size = (tDir->fileInfo(index).size()/1024);
        if ( (size/1024) < 1)
           ui->imgSize->setText(QString::number(size)+"Kb");
        else
        {
            size/=1024;
            ui->imgSize->setText(QString::number(size)+"Mb");
         }
         QImage img(fpath+"/"+fname);
         QImage imgPreview = img.scaled(200,200, Qt::KeepAspectRatio);
         QPalette* pal = new QPalette();
         pal->setBrush(ui->widget->backgroundRole(), QBrush(imgPreview));

         ui->widget->setPalette(*pal);
         ui->widget->setAutoFillBackground(true);
         ui->widget->setFixedSize(imgPreview.width(), imgPreview.height());
         dir->setPath(fpath);

         imageList.append(fpath+fname);
    }
}

void OpenFile::on_open_clicked()
{
    if (!imageList.isEmpty())
        close();
}
