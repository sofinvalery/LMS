#ifndef COURSEADDER_H
#define COURSEADDER_H

#include <QWidget>

namespace Ui {
class CourseAdder;
}

class CourseAdder : public QWidget
{
    Q_OBJECT

public:
    explicit CourseAdder(QWidget *parent = nullptr);
    ~CourseAdder();

private:
    Ui::CourseAdder *ui;
};

#endif // COURSEADDER_H
