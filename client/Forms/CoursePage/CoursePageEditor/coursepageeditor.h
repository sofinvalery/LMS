#ifndef COURSEPAGEEDITOR_H
#define COURSEPAGEEDITOR_H

#include <QWidget>
#include "Forms/CoursePage/coursepage.h"


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

private:
    Ui::CoursePageEditor *ui;
    CoursePage * coursepage;
    int AddingStatus = 0; // 1 - тест, 2 - файл, 3 - дз, 4 - пояснение
    int DeletingStatus = 0;
};

#endif // COURSEPAGEEDITOR_H
