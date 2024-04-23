#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QWidget>
#include <../../common/course/course.h>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(Course* course,QWidget *parent = nullptr);
    void setName(QString name);
    void setIMG(QString path);
    ~MyWidget();
private:
    Ui::MyWidget *ui;
    Course * course;
};

#endif // MYWIDGET_H
