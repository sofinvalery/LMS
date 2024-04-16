#include "potokadder.h"
#include "ui_potokadder.h"
#include <QScreen>
#include <QFileDialog>

PotokAdder::PotokAdder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PotokAdder)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "border-top: 3px solid lightgrey;"
        "}");

    QScreen* scr = QGuiApplication::primaryScreen();

    this->resize( scr->availableGeometry().width(), scr->availableGeometry().height() - 20);
    ui->groupBox->setMinimumSize(this->frameGeometry().width(),this->frameGeometry().height() - 20);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->resize(this->frameGeometry().width()-25-350,this->frameGeometry().height() - 20);
    this->move(0, 90);
    GroupNames.clear();
    GroupErrors.clear();
    GroupNames.append(ui->Group_name);
    GroupErrors.append(ui->Error_Box);
    qDebug() << ui->Group_name->geometry();
}

PotokAdder::~PotokAdder()
{
    delete ui;
}

void PotokAdder::on_Add_line_clicked()
{
    counter++;
    GroupNames.append(new QLineEdit(ui->scrollAreaWidgetContents));
    GroupErrors.append(new QLabel(ui->scrollAreaWidgetContents));
    GroupNames[counter]->setGeometry(ui->Group_name->x(), counter == 1 ? ui->Group_name->y()*2 : ui->Group_name->y()*(counter + 1), ui->Group_name->width(), ui->Group_name->height());
    GroupErrors[counter]->setGeometry(ui->Error_Box->x(), counter == 1 ? ui->Error_Box->y()*2 : ui->Error_Box->y()*(counter + 1), ui->Error_Box->width(), ui->Error_Box->height());
    GroupErrors[counter]->setText(ui->Error_Box->text());
    GroupNames[counter]->show();
    GroupErrors[counter]->show();
    if (counter*(ui->Group_name->height()*4) > this->frameGeometry().height() - 20)
        ui->scrollAreaWidgetContents->setMinimumHeight(counter*(ui->Group_name->height()*4));
    //qDebug() << GroupNames[counter]->geometry();
    //GroupNames[counter]->move(ui->Group_name->x(), ui->Group_name->y()*counter+1);

}


void PotokAdder::on_Add_line_2_clicked()
{
    if (counter > 0){
    GroupErrors[counter]->close();
    GroupErrors.removeAt(counter);
    GroupNames[counter]->close();
    GroupNames.removeAt(counter);
    if (counter*(ui->Group_name->height()*4) < this->frameGeometry().height() - 20)
        ui->scrollAreaWidgetContents->setMinimumHeight(this->frameGeometry().height() - 20);
    counter--;
    }
}


void PotokAdder::on_FoundExcel_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Выбор таблицы", "C:\\", "Excel files (*.xlsx *.xls);");

    ui->Excel_Path->setText(path);
}

