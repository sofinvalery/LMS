#ifndef COURSEDOWNLOAD_H
#define COURSEDOWNLOAD_H


#include "../../../../common/course/course_components/coursepdf.h"
#include <QWidget>
#include <QPixmap>


namespace Ui {
class CourseDownload;
}

class CourseDownload : public QWidget
{
    Q_OBJECT

public:
    explicit CourseDownload(CourseComponent * pdf, QWidget *parent = nullptr);
    ~CourseDownload();

private:
    Ui::CourseDownload *ui;
    CoursePdf * pdf;
    QPixmap * icon;
};

#endif // COURSEDOWNLOAD_H
