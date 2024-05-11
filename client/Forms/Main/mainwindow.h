#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Forms/MyWidget/mywidget.h"
#include "../common/authentication/authentication.h"
#include "Forms/CoursesMPWidget/coursesmpwidget.h"
#include "Forms/Profile/profile.h"
#include "Forms/Score/score.h"
#include "StyleManager/stylemanager.h"
#include "../Download/download.h"
#include "Forms/AddGroup/addgroup.h"
#include "Forms/GroupEditor/groupeditor.h"
#include "Forms/PotokAdder/potokadder.h"
#include "Forms/CourseAdder/courseadder.h"
#include "Forms/Loader/loader.h"

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
    Download *getDownload() const;

    Loader *getDialogLoader() const;
    void raiseDownloadAndLoader();

    QWidget *getWidget() const;

public slots:
    void ShowManePage();
    void clickCoursePage(Course* course);
    void on_mainButton_clicked();


private slots:
    void ShowAddingPotok();
    void ShowAddingGroup();
    void ShowAddingCourse();
    void ShowEditGroup();
    void ShowCoursePage(Course* course);
    void ShowScore();

    void on_exitButton_clicked();
    void on_profileButton_clicked();
    void on_scoreButton_clicked();
    void on_addCourseButton_clicked();
    void on_addPotokButton_clicked();
    void on_addGroupButton_clicked();
    void on_editGroupButton_clicked();
    void doAllButtonClicked();

    void on_loaderButton_clicked();

private:
    Ui::MainWindow *ui;
    QWidget * widget=nullptr;
    Download * download = new Download();
    Loader* dialogLoader = new Loader();
    Profile* dialogProfile = nullptr;
    void on_button_clicked(QPushButton* clickedButton);
    //MyWidget * course[25];


};
#endif // MAINWINDOW_H
