#include "about.h"
#include "ui_about.h"
#include <QColor>
#include <QPalette>

About::About(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setWindowTitle("Справка");
    QPalette palette = ui->textBrowser->palette();

    palette.setColor(QPalette::Base, QColor("#ECECEC"));
    ui->textBrowser->setPalette(palette);

    on_aboutDev_clicked();

}

About::~About()
{
    delete ui;
}

void About::on_help_clicked()
{
    ui->textBrowser->setText("<h3><p align='center'>Создание пирамиды изображений</p></h3>"
                      "<p>Для добавления изображения необходимо выбрать в меню 'File'  пункт"
                      " 'Open image'. 'Open image' открывает диалоговое окно, в котором можно отметить"
                      " одно или несколько изображений. Выбрать можно только изображения в формате"
                      " jpeg, png или gif. При выборе корректного изображения сбоку появляется превью "
                      "изображения, а так же информация о нем.</p><p>Также выбрать изображение можно при "
                      "запуске из командной строки. Для этого необходимо указать ключ '--image' "
                      "и далее через запятую указать путь до изображений. Еще один ключ, '--rate' позволяет "
                      "указать значение коэффициента уменьшения. По умолчанию это значение равно двум."
                       " Указывать  коэффициент можно и в уже открытом приложении: в окне справа можно ввести"
                      " значение от 1.5 до 100. По окончанию ввода нового значения автоматически создастся "
                      "новый список слоев, и загрузится слой с размером оригинального изображения.</p>");

}

void About::on_aboutDev_clicked()
{
    ui->textBrowser->setText("<br><br><h3><p align='center'>Разработчик</p></h3>"
        "<p align='center'>Разработала Пархоменко Анна Александровна, "
       "<p align='center'>Новосибирск</p> <p align='center'> 2018г.</p>");
}
