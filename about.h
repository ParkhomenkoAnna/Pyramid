#ifndef About_H
#define About_H

#include <QDialog>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget * parent = 0);
    ~About();

private slots:
    void on_help_clicked();
    void on_aboutDev_clicked();

private:
    Ui::About *ui;
};

#endif // About_H
