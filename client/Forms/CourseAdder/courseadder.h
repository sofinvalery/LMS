#ifndef COURSEADDER_H
#define COURSEADDER_H

#include <QWidget>
#include "Forms/MyWidget/mywidget.h"

namespace Ui {
class CourseAdder;
}

class CourseAdder : public QWidget
{
    Q_OBJECT

public:
    explicit CourseAdder(QWidget *parent = nullptr);
    MyWidget * course;
    ~CourseAdder();

private slots:
    void on_Apply_clicked();

private:
    Ui::CourseAdder *ui;
};

#endif // COURSEADDER_H
