#include "jsonmanager.h"

typedef QJsonObject (*Action)(QJsonObject,Authentication **auth);

static Action Actions[] ={
    [LOGINING] = logining,
    [GETMAINPAGE] = getMainPage,
    [GETCOURSECOMPONENTS] = getCourseComponents,
    [GETTESTQUESTION] = getTestQuestions,
    [SETNEWGROUP] = setNewGroup,
    [SETNEWTEST] = setNewTest,
    [SETNEWCOURSE] = setNewCourse,
    [RECONECT] = reconect,
    [GETINFOFORADDINGPOTOK] = getInfoForAddPotok,
    [SETNEWPOTOK] = setNewPotok,
    [GETINFOFORADDINGGROUP] = getInfoForAddGroup,
    [GETINFOFORAADDINGCOURSE]= getInfoForAddCourse,
    [GETINFOFOREDITGROUP] = getInfoForEditGroup,
    [GETGROUP]= getGroup,
    [UPDATEGROUP] = updateGroup
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

QJsonObject setNewGroup(QJsonObject json,Authentication **auth)
{
    Group* group = Group::Deserialize(json);
    DatabaseManager db;
    db.AddNewGroup(group);
    QJsonObject sendjson;
    delete group;
    return sendjson;
}

QJsonObject setNewTest(QJsonObject json,Authentication **auth)
{

}

QJsonObject setNewCourse(QJsonObject json,Authentication **auth)
{
    QString teachersGroupName = json["teachersGroupName"].toString();
    QString unionName = json["unionName"].toString();
    Course * course = Course::Deserialize(json["Course"].toObject(),true);
    DatabaseManager db;
    db.AddNewCourse(teachersGroupName,unionName,course);
    QJsonObject sendjson;
    delete course;
    return sendjson;

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

QJsonObject getInfoForAddGroup(QJsonObject json, Authentication **auth)
{
    QJsonObject sendjson;
    sendjson["Data"]=getInfoAboutAllGroup(json,auth);
    sendjson["Action"]=GETINFOFORADDINGGROUP;
    return sendjson;
}

QJsonObject getInfoForAddCourse(QJsonObject json, Authentication **auth)
{
    DatabaseManager db;
    QList<QString> TeacherGroupNames = db.GetEveryTeacherGroupName();
    QList<QString> PotokNames = db.GetEveryUnionName();
    QJsonObject sendjson;
    QJsonArray groupsComponents;
    for (auto & user : TeacherGroupNames)
        groupsComponents.append(user);
    QJsonArray potoksComponents;
    for (auto & user : PotokNames)
        potoksComponents.append(user);
    sendjson["Action"]=GETINFOFORAADDINGCOURSE;
    QJsonObject temp;
    temp["TeacherGroupNames"]=groupsComponents;
    temp["PotokNames"]=potoksComponents;
    sendjson["Data"]=temp;
    return sendjson;
}

QJsonObject getInfoAboutAllGroup(QJsonObject json, Authentication **auth)
{
    DatabaseManager db;
    QList<QString> GroupName = db.GetEveryGroupName();
    QJsonArray groupsComponents;
    for (auto & user : GroupName)
        groupsComponents.append(user);
    QJsonObject temp;
    temp["GroupName"]=groupsComponents;
    return temp;
}

QJsonObject getInfoForEditGroup(QJsonObject json, Authentication **auth)
{
    QJsonObject sendjson;
    sendjson["Data"]=getInfoAboutAllGroup(json,auth);
    sendjson["Action"]=GETINFOFOREDITGROUP;
    return sendjson;
}

QJsonObject getGroup(QJsonObject json, Authentication **auth)
{
    DatabaseManager db;
    QString groupName = json["groupName"].toString();
    Group* group = db.GetGroupByName(groupName);
    QJsonObject sendjson;
    sendjson["Action"]=GETGROUP;
    sendjson["Data"]=group->Serialize();
    return sendjson;
}

QJsonObject updateGroup(QJsonObject json, Authentication **auth)
{
    DatabaseManager db;
    Group* gr = Group::Deserialize(json);
    db.UpdateGroup(gr);
    QJsonObject sendjson;
    for(auto t:gr->getParticipants())
        delete t;
    delete gr;
    return sendjson;
}
