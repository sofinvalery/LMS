#ifndef ADDGROUP_H
#define ADDGROUP_H
#include <QWidget>
#include <QList>
#include <QLineEdit>
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

    void on_createButton_clicked();

private:
    Ui::AddGroup *ui;

    QList<QLineEdit*> nameList;
    QList<QLabel*> numberList;

    int heightLine = 0;
    int count = 1;
};

#endif // ADDGROUP_H
