#ifndef POTOKADDER_H
#define POTOKADDER_H

#include <QWidget>
#include<QList>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class PotokAdder;
}

class PotokAdder : public QWidget
{
    Q_OBJECT

public:
    explicit PotokAdder(QWidget *parent = nullptr);
    QList<QLineEdit*> GroupNames;
    QList<QLabel*> GroupErrors;
    int counter = 0;
    ~PotokAdder();

private slots:
    void on_Add_line_clicked();

    void on_Add_line_2_clicked();

    void on_FoundExcel_clicked();

    void on_Create_potok_clicked();

private:
    Ui::PotokAdder *ui;
};

#endif // POTOKADDER_H
