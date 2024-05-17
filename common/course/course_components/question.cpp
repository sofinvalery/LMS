#include "question.h"


inline void Question::setStudentAnswer(const QList<int32_t> &newStudentAnswer)
{
    studentAnswer = newStudentAnswer;
}

inline int32_t Question::getType() const
{
    return type;
}

inline QList<QString> Question::getAnswers() const
{
    return answers;
}

inline QString Question::getQuestion() const
{
    return question;
}

QJsonObject Question::Serialize()
{


    QJsonObject json;
    json["question"]=question;



    QJsonArray ans;
    for (auto & user : answers)
        ans.append(user);

    json["answers"]=ans;



    json["type"]=type;



    QJsonArray studAns;
    for (auto & user : studentAnswer)
        studAns.append(user);
    json["studentAnswer"]= studAns;




    return json;
}

Question* Question::Deserialize(QJsonObject jsonObj)
{


    QList<QString> ans;
    QJsonArray ansArray=jsonObj["answers"].toArray();
    for(int i=0;i<ansArray.size();i++)
        ans.append(ansArray[i].toString());

    QList<int32_t> studAns;
    QJsonArray studAnsArray=jsonObj["studentAnswer"].toArray();
    for(int i=0;i<studAnsArray.size();i++)
        studAns.append(studAnsArray[i].toInt());
    Question* t= new Question(jsonObj["question"].toString(),ans,
                               jsonObj["type"].toInt(),studAns);
    return t;
}

void Question::setQuestion(const QString &newQuestion)
{
    question = newQuestion;
}

void Question::setAnswers(const QList<QString> &newAnswers)
{
    answers = newAnswers;
}

void Question::setType(int32_t newType)
{
    type = newType;
}
