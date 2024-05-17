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
    explicit TestEditor(QList<Question*> questions, QWidget *parent = nullptr);
    ~TestEditor();
    void OneAnswerToggle(bool status);
    void ManyAnswersToggle(bool status);
    void PossibleAnswersToggle(bool status);

private slots:
    void on_exitButton_clicked();

    void on_OneAnswerButton_toggled(bool checked);

    void on_ManyAnswersButton_toggled(bool checked);

    void on_DetailedAnswerButton_toggled(bool checked);

    void on_ApplyChangesButton_clicked();

private:
    Ui::TestEditor *ui;
    QList<Question*> questions;
    int32_t typeq = 0;
    bool IsAdding = false;

                                                                                    // QString question;
                                                                                    // QList<QString> answers;
                                                                                    // int32_t type;
                                                                                    // QList<int32_t> studentAnswer;
};

#endif // TESTEDITOR_H
