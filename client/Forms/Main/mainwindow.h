#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Forms/MyWidget/mywidget.h"
#include "../common/authentication/authentication.h"
#include "Forms/CoursesMPWidget/coursesmpwidget.h"
#include "Forms/Profile/profile.h"
#include "Forms/Score/score.h"
#include "StyleManager/stylemanager.h"
<<<<<<< HEAD
#include "../Download/download.h"
=======
>>>>>>> 80ea3dd (added new widgets: notification, group editor. Add group 7.8)
#include "Forms/AddGroup/addgroup.h"
#include "Forms/GroupEditor/groupeditor.h"
#include "Forms/PotokAdder/potokadder.h"

#include "Forms/CourseAdder/courseadder.h"

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
public slots:    void ShowManePage();


private slots:
    void on_exitButton_clicked();
    void on_profileButton_clicked();
    void on_scoreButton_clicked();
    void on_mainButton_clicked();
    void on_addCourseButton_clicked();
    void on_addPotokButton_clicked();
    void on_addGroupButton_clicked();
    void on_editGroupButton_clicked();

private:
    Ui::MainWindow *ui;
    QWidget * widget=nullptr;
    Download * download = new Download();
    //MyWidget * course[25];

};
#endif // MAINWINDOW_H
