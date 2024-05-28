#ifndef TESTPASSING_H
#define TESTPASSING_H

#include <QWidget>
#include "../../../common/course/course_components/question.h"
#include "Forms/TestWidget/testwidget.h"
#include <QTimer>
#include <QTime>

struct QuestionAnswers{
    int32_t type;
    QList<int32_t> Answers;
    QString DetailedAnswer = "";

};


namespace Ui {
class TestPassing;
}

class TestPassing : public QWidget
{
    Q_OBJECT

public:
    explicit TestPassing(TestWidget * testwidget, QWidget *parent = nullptr);
    ~TestPassing();

private slots:
    void on_CurrentQuestionSpinBox_valueChanged(int arg1);
    void HidePossibleAnswers(bool hide);
    void HideRadioButtons(bool hide);
    void CleanCheckBoxes();
    void HideCheckBoxes(bool hide);


    void on_Answer1RadioButton_toggled(bool checked);

    void on_Answer2RadioButton_toggled(bool checked);

    void on_Answer3RadioButton_toggled(bool checked);

    void on_Answer4RadioButton_toggled(bool checked);

    void on_Answer1CheckBox_toggled(bool checked);

    void on_Answer2CheckBox_toggled(bool checked);

    void on_Answer3CheckBox_toggled(bool checked);

    void on_Answer4CheckBox_toggled(bool checked);

    void on_DetailedAnswerLineEdit_editingFinished();

    double SummPoints();

    void on_EndTestButton_clicked();

    void updateTimer();

private:
    Ui::TestPassing *ui;
    QList<Question*> questionList;
    QList<QuestionAnswers*> answers;
    TestWidget * testWidget;

    QTimer * timer;
    QTime timeLeft;
};


#endif // TESTPASSING_H
