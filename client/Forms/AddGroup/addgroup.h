#ifndef ADDGROUP_H
#define ADDGROUP_H
#include <QWidget>
#include <QLineEdit>
#include <QScreen>
#include <QFileDialog>
#include <QLabel>

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
    void on_studentBox_clicked();

    void on_teacherBox_clicked();

    void on_addButton_clicked();

    void on_createButton_clicked(); //кнопка создания

    void on_FindExcelButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::AddGroup *ui;

    QList<QLineEdit*> nameList;  //список фио
    QList<QLabel*> numberList;
    int heightLine = 0;
    int count = 0;
};

#endif // ADDGROUP_H
