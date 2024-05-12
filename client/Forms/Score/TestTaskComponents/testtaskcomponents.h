#ifndef TESTTASKCOMPONENTS_H
#define TESTTASKCOMPONENTS_H

#include <QWidget>

namespace Ui {
class testTaskComponents;
}

class testTaskComponents : public QWidget
{
    Q_OBJECT

public:
    explicit testTaskComponents(QString courseName = "CourseName", int currentScore = 0, int maxScore = 100, QWidget *parent = nullptr);
    ~testTaskComponents();

private:
    Ui::testTaskComponents *ui;
};

#endif // TESTTASKCOMPONENTS_H
