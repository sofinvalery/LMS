#ifndef COURSEPAGEEDITOR_H
#define COURSEPAGEEDITOR_H

#include <QWidget>
#include "Forms/CoursePage/coursepage.h"
#include <QPushButton>

namespace Ui {
class CoursePageEditor;
}

class CoursePageEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CoursePageEditor(CoursePage * coursepage, QWidget *parent = nullptr);
    ~CoursePageEditor();
private slots:
    void on_LoadFileButton_clicked();

    void on_AddWidgetButton_clicked();

    void on_EditWidgetButton_clicked();

    void on_DeleteWidgetButton_clicked();

    void on_DoneButton_clicked();

    void on_AddFileButton_clicked();

    void on_AddTextButton_clicked();

    void on_AddTestButton_clicked();

    void on_AddDzButton_clicked();

    void on_exitButton_clicked();

    void on_ChooseButton_clicked();

private:
    Ui::CoursePageEditor *ui;
    CoursePage * coursepage;
    int AddingStatus = 0; // 1 - тест, 2 - файл, 3 - дз, 4 - пояснение
    int DeletingStatus = 0;
    int EditingStatus = 0; // 1 - тест, 2 - файл, 3 - дз, 4 - пояснение

    void on_mainButton_clicked(QPushButton* clickedButton);
    void on_mainButton_clickedAgain();
    void on_AddButton_clicked(QPushButton* clickedButton);
    void on_AddButton_clickedAgain();

    CourseTest * temptest;
    CoursePdf * tempfile;
    CourseTask * tempdz;
    CourseTutorials * temptext;

};

#endif // COURSEPAGEEDITOR_H
