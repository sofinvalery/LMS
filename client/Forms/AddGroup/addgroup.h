#ifndef ADDGROUP_H
#define ADDGROUP_H
#include <QWidget>
#include <QLineEdit>
#include <QScreen>
#include <QFileDialog>
#include <QLabel>
#include "XlsxUtils/xlsxutils.h"

namespace Ui {
class AddGroup;
}

class AddGroup : public QWidget
{
    Q_OBJECT

public:
    explicit AddGroup(QWidget *parent = nullptr);
    ~AddGroup();

private slots:
    void on_studentBox_clicked(); //чекбокс студентов

    void on_teacherBox_clicked(); //чекбокс преподов

    void on_addButton_clicked(); //кнопка добавления

    void on_createButton_clicked(); //кнопка создания

    void on_FindExcelButton_clicked(); //выбрать эксель

    void on_deleteButton_clicked(); //удалить чела

    void on_exampleExcelButton_clicked();

private:
    Ui::AddGroup *ui;

    QList<QLineEdit*> nameList;  //список фио
    QList<QLabel*> numberList;
    int heightLine = 0;
    int count = 0;
    AddingData* data= nullptr;
};

#endif // ADDGROUP_H
