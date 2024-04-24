#include "jsonmanager.h"

typedef QJsonObject (*Action)(QJsonObject,Authentication **auth);

static Action Actions[] ={
    [LOGINING] = logining,
    [GETMAINPAGE] = getMainPage,
    [GETCOURSECOMPONENTS] = getCourseComponents,
    [GETTESTQUESTION] = getTestQuestions,
    [SETNEWGROUP] = setNewGroupStudents,
    [SETNEWTEST] = setNewTest,
    [SETNEWCOURSE] = setNewCourse,
    [RECONECT] = reconect,
    [GETINFOFORADDINGPOTOK] = getInfoForAddPotok,
    [SETNEWPOTOK] = setNewPotok

};

QJsonObject jsonManager(QJsonObject json,Authentication **auth)
{
    QJsonObject data=json["Data"].toObject();
    TransferEnum e = (TransferEnum)json["Action"].toInt();
    if((e==LOGINING || e==RECONECT))
    return Actions[e](data,auth);
    if((*auth)!=nullptr && (*auth)->IsAuthenticated())
        return Actions[e](data,auth);
    else
    {
        QJsonObject sendjson;
        return  sendjson;
    }
}

QJsonObject logining(QJsonObject json,Authentication **auth)
{
    QJsonObject sendjson;
    *auth = Authentication::Deserialize(json);
    (*auth)->HashPassword();
    DatabaseManager db;
    QList<Course*> list;
    if(db.Login(*auth))
        list = db.GetMainPage(*auth);
    /*QList<Course*> list= {new Course(5,"maths","aaaaa", QDate(1999,9,9),QDate(2000,1,1),20,100),
                            new Course(15,"phisyc","bbbbb", QDate(2004,4,4),QDate(2005,1,1),11,80)};
    auth->SetInformationAfterAuthentication("Max","bbbbb",ADMIN,55,QList<QString>{"O725B"});*/
    QJsonArray components;
    for (auto & user : list)
        components.append(user->Serialize());
    sendjson["Action"]=LOGINING;
    QJsonObject temp;
    temp["Authentication"]=(*auth)->Serialize();
    temp["CourseList"]=components;
    sendjson["Data"]=temp;
    return sendjson;
}
QJsonObject reconect(QJsonObject json,Authentication **auth){
    QJsonObject sendjson;
    delete *auth;
    *auth = Authentication::Deserialize(json);
    DatabaseManager db;
    if(!db.Login(*auth))
        (*auth)->setIsAuthenticated(false);
    sendjson["Action"]=RECONECT;
    return sendjson;
}

QJsonObject getMainPage(QJsonObject json,Authentication **auth)
{
    DatabaseManager db;
    QList<Course*> list = db.GetMainPage(*auth);
    QJsonObject sendjson;
    QJsonArray components;
    for (auto & user : list)
        components.append(user->Serialize());
    sendjson["Action"]=GETMAINPAGE;
    QJsonObject temp;
    temp["CourseList"]=components;
    sendjson["Data"]=temp;
    return sendjson;
}

QJsonObject getCourseComponents(QJsonObject json,Authentication **auth)
{

}

QJsonObject getTestQuestions(QJsonObject json,Authentication **auth)
{

}

QJsonObject setNewGroupStudents(QJsonObject json,Authentication **auth)
{

}

QJsonObject setNewTest(QJsonObject json,Authentication **auth)
{

}

QJsonObject setNewCourse(QJsonObject json,Authentication **auth)
{

}

QJsonObject setNewPotok(QJsonObject json, Authentication **auth)
{

    QJsonArray groupsComponents=json.value("groupsList").toArray();
    QList<QString> groupList;
    for(qsizetype i=0;i<groupsComponents.size();i++)
        groupList.append(groupsComponents[i].toString());

    QString unionName=json.value("unionName").toString();

    DatabaseManager db;
    db.AddGroupsToUnion(groupList,unionName);
    QJsonObject send;
    return send;
}

QJsonObject getInfoForAddPotok(QJsonObject json, Authentication **auth)
{
    DatabaseManager db;
    QList<QString> studentGroupName = db.GetAllStudentGroupName();
    QList<QString> potoksName = db.GetEveryUnionName();
    QJsonObject sendjson;
    QJsonArray groupsComponents;
    for (auto & user : studentGroupName)
        groupsComponents.append(user);
    QJsonArray potoksComponents;
    for (auto & user : potoksName)
        potoksComponents.append(user);
    sendjson["Action"]=GETINFOFORADDINGPOTOK;
    QJsonObject temp;
    temp["studentGroupName"]=groupsComponents;
    temp["potoksName"]=potoksComponents;
    sendjson["Data"]=temp;
    return sendjson;
}
