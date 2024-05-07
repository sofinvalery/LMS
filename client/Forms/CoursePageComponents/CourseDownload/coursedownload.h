#ifndef COURSEDOWNLOAD_H
#define COURSEDOWNLOAD_H


#include "../../../../common/course/course_components/coursemediafiles.h"
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
    void SetTextOnButton(QString buttontext);

private slots:
    void on_DownloadButton_clicked();

private:
    Ui::CourseDownload *ui;
    CourseMediaFiles * pdf;
    QPixmap * icon;
};

#endif // COURSEDOWNLOAD_H
