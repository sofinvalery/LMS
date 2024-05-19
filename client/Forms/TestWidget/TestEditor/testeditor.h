#ifndef TESTEDITOR_H
#define TESTEDITOR_H

#include <QWidget>
#include "Forms/TestWidget/testwidget.h"
#include "../../../../common/course/course_components/question.h"
#include <QList>

namespace Ui {
class TestEditor;
}

class TestEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TestEditor(CourseTest * test, QWidget *parent = nullptr);
    ~TestEditor();


private slots:
    void on_exitButton_clicked();

    void on_OneAnswerButton_toggled(bool checked);

    void on_ManyAnswersButton_toggled(bool checked);

    void on_DetailedAnswerButton_toggled(bool checked);

    void on_ApplyChangesButton_clicked();

    void OneAnswerToggle(bool status);

    void ManyAnswersToggle(bool status);

    void PossibleAnswersToggle(bool status);

    QList<int32_t> WhatRadioButtonIsChecked();

    QList<int32_t> WhatCheckBoxIsChecked();

    void on_CurrentQuestionSpinBox_valueChanged(int arg1);

    void on_AddNewQuestionButton_clicked();

    void CleanAll();

private:
    Ui::TestEditor *ui;
    //QList<Question*> questions;
    CourseTest * test;
    int32_t typeq = -1;
    bool IsAdding = false;

                                                                                    // QString question;
                                                                                    // QList<QString> answers;
                                                                                    // int32_t type;
                                                                                    // QList<int32_t> studentAnswer;
};

#endif // TESTEDITOR_H
