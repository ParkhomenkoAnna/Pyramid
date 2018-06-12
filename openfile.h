#ifndef OPENFILE_H
#define OPENFILE_H

#include <QDialog>
#include <QTreeView>
#include <QFileSystemModel>


namespace Ui {
class OpenFile;
}

class OpenFile : public QDialog
{
    Q_OBJECT

public:
    explicit OpenFile(QWidget *parent = 0);
    ~OpenFile();
     QString  fname, fpath;
     QStringList imageList;
     QTreeView * masterTree, *newTree;


private slots:
      void on_listView_clicked(const QModelIndex &index);
      void on_open_clicked();
      void on_clicked(const QModelIndex &);
      void addedNewTree(QFileSystemModel *,const QModelIndex );


private:
    QFileSystemModel *lDir, *tDir;
    QDir * dir;
    Ui::OpenFile *ui;
};

#endif // OPENFILE_H
