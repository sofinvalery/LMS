#ifndef COURSETEXT_H
#define COURSETEXT_H

#include <QWidget>
#include "../../../../common/course/course_components/coursetutorials.h"


namespace Ui {
class CourseText;
}

class CourseText : public QWidget
{
    Q_OBJECT

public:
    explicit CourseText(CourseComponent * text, QWidget *parent = nullptr);
    ~CourseText();
    void setText(QString text);

private:
    Ui::CourseText *ui;
    CourseTutorials * text;
};

#endif // COURSETEXT_H
