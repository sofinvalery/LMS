#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QWidget>

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

private:
    Ui::AddGroup *ui;
};

#endif // ADDGROUP_H
