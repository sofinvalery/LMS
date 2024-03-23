#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Question: public QObject
{
    Q_OBJECT

public:
    explicit Question(QString question, QList<QString> answers, int32_t type,
                      QList<int32_t> studAns=QList<int32_t>(),QObject *parent = nullptr)
        :QObject(parent)
    {
        this->question=question;
        this->answers=answers;
        this->type=type;
        this->studentAnswer=studAns;
    }
    explicit Question(QObject *parent = nullptr):QObject(parent){};
    void setStudentAnswer(const QList<int32_t> &newStudentAnswer);

    int32_t getType() const;

    QList<QString> getAnswers() const;

    QString getQuestion() const;

    QJsonObject Serialize();

    static Question* Deserialize(QJsonObject json);

private:
    QString question;
    QList<QString> answers;
    int32_t type;
    QList<int32_t> studentAnswer;
};




#endif // QUESTION_H
