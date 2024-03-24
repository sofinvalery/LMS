#include "jsonmaneger.h"


QJsonObject jsonManager(QJsonObject json,Authentication *auth)
{
    QJsonObject data=json["Data"].toObject();
    TransferEnum e = (TransferEnum)json["Action"].toInt();
    if(auth==nullptr&& e!=LOGINING)
        throw std::exception();
    return Actions[e](data,auth);
}

QJsonObject logining(QJsonObject json,Authentication *auth)
{

}

QJsonObject getMainPage(QJsonObject json,Authentication *auth)
{

}

QJsonObject getCourseComponents(QJsonObject json,Authentication *auth)
{

}

QJsonObject getTestQuestions(QJsonObject json,Authentication *auth)
{

}

QJsonObject setNewGroupStudents(QJsonObject json,Authentication *auth)
{

}

QJsonObject setNewTest(QJsonObject json,Authentication *auth)
{

}

QJsonObject setNewCourse(QJsonObject json,Authentication *auth)
{

}
