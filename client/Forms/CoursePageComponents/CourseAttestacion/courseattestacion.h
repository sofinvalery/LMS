#ifndef COURSEATTESTACION_H
#define COURSEATTESTACION_H

#include <QWidget>

#include "../../../../common/course/course_components/coursetest.h"
#include "QPixmap"
#include "Forms/TestWidget/testwidget.h"


namespace Ui {
class CourseAttestacion;
}

class CourseAttestacion : public QWidget
{
    Q_OBJECT

public:
    explicit CourseAttestacion(CourseComponent * test, QWidget *parent = nullptr);
    ~CourseAttestacion();
    void SetTextOnButton(QString buttontext);

private slots:
    void on_DownloadButton_clicked();
    void showTestWidjet(QJsonObject json);

private:
    Ui::CourseAttestacion *ui;
    CourseTest * test;
    QPixmap * icon;
    TestWidget * testwidget;

};

#endif // COURSEATTESTACION_H
