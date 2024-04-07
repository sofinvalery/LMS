#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Forms/MyWidget/mywidget.h"
#include "../common/authentication/authentication.h"
#include "FontManager/fontmanager.h"
#include "Forms/CoursesMPWidget/coursesmpwidget.h"
#include "Forms/Profile/profile.h"
#include "Forms/Score/score.h"
#include <QScreen>


// #include <QScrollArea>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_exitButton_clicked();
    void on_profileButton_clicked();
    void on_scoreButton_clicked();
    void on_mainButton_clicked();
    void on_addCourseButton_clicked();
    void on_addPotokButton_clicked();
    void on_addGroupButton_clicked();
private:
    Ui::MainWindow *ui;
    CoursesMPWidget * courses = new CoursesMPWidget();
    Profile* profile = new Profile();
    Score* score = new Score();

    //MyWidget * course[25];

};
#endif // MAINWINDOW_H
