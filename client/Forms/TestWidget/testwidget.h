#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "../../../common/course/course_components/coursetest.h"
#include "TestEditor/testeditor.h"

namespace Ui {
class TestWidget;
}

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget(CourseTest * test, QWidget *parent = nullptr);
    ~TestWidget();

private slots:
    void on_BackButton_clicked();

    void on_EditTestButton_clicked();

private:
    Ui::TestWidget *ui;
    CourseTest * test;
};

#endif // TESTWIDGET_H
