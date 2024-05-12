#include "score.h"
#include "ui_score.h"
#include "StyleManager/stylemanager.h"
#include "ClientState/clientstate.h"

Score::Score(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Score)
{
    ui->setupUi(this);
    StyleManager::GetInstance()->setWidgetGroupBoxStyle(this, ui->groupBox, 90);

    StyleManager::GetInstance()->setScrollAreaStyle(ui->scrollArea, true);
    ui->scrollArea->setFixedSize(StyleManager::GetInstance()->getScreenWidth(), StyleManager::GetInstance()->getScreenHeight());
    for (int i = 0; i < ClientState::GetInstance()->getListCourses().size(); i++)
    {
        ScoreComponents* score = new ScoreComponents(ClientState::GetInstance()->getListCourses()[i]->GetTitle(),
                                                     ClientState::GetInstance()->getListCourses()[i]->GetPoints(),
                                                     ClientState::GetInstance()->getListCourses()[i]->getMaxSumpoints(), ui->scrollAreaWidgetContents,
                                                     ClientState::GetInstance()->getListCourses()[i]);
        scoreList.append(score);
        connect(score, SIGNAL(showPathCourseScore(Course*)), this, SLOT(showPathCourseScore(Course*)));
        score->move(20, heightLine);
        heightLine += 90;
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(heightLine + 120);
}

Score::~Score()
{
    delete ui;
}

void Score::showPathCourseScore(Course *course)
{
    bool edit = false;
    int index;
    for(index=0;index < scoreList.size();index++)
    {
        if(qobject_cast<ScoreComponents*>(sender()) == scoreList[index])
            break;
    }
    if (PathCourseScoreList.size() > 0)
    {
        for (auto temp : PathCourseScoreList)
        {
            temp->close();
            delete temp;
        }
        PathCourseScoreList.clear();
        heightLine = 20;
        for (auto temp : scoreList)
        {
            temp->move(20, heightLine);
            heightLine += 90;
        }
    }
    heightLine = 20 + 90 * index + 90;
    for (CourseComponent* temp : course->getListComponents())
    {
        CourseTest* courseTest;
        CourseTask* courseTask;
        if ((courseTask = qobject_cast<CourseTask*>(temp)) != nullptr)
        {
            testTaskComponents* task = new testTaskComponents(courseTask->getTitle(),
                                                         courseTask->getVerdict(),
                                                              courseTask->getMaxMark(), ui->scrollAreaWidgetContents); //nazvanie sdelayte
            PathCourseScoreList.append(task);
            edit = true;
            task->move(50, heightLine);
            task->show();
            heightLine += 70;
        }
        else if ((courseTest = qobject_cast<CourseTest*>(temp)) != nullptr)
        {
            testTaskComponents* test = new testTaskComponents(courseTest->getTitle(),
                                                         courseTest->getVerdict(),
                                                         courseTest->getMaxMark(), ui->scrollAreaWidgetContents);
            PathCourseScoreList.append(test);
            edit = true;
            test->move(50, heightLine);
            test->show();
            heightLine += 70;
        }
    }
    for (index++;index < scoreList.size(); index++)
    {
        scoreList[index]->move(20, heightLine);
        heightLine += 90;
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(heightLine + 120);
}
