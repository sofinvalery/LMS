#ifndef SCORE_H
#define SCORE_H

#include <QWidget>
#include "ScoreComponents/scorecomponents.h"
#include "TestTaskComponents/testtaskcomponents.h"

namespace Ui {
class Score;
}

class Score : public QWidget
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = nullptr);
    ~Score();
private slots:
    void showPathCourseScore(Course* course);
private:
    QList<ScoreComponents*> scoreList;
    QList<testTaskComponents*> PathCourseScoreList;
    int heightLine = 20;
    Ui::Score *ui;
};

#endif // SCORE_H
