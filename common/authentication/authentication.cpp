#include "authentication.h"


Authentication::Authentication(QString login, QString password,int32_t id, QString fio, QString urlAvatar,
                               EnumRoles role, QList<QString> groups, bool isAuthenticated, QObject *parent):QObject(parent)
{
    this->login=login;
    this->id=id;
    this->password=password;
    this->fio=fio;
    this->urlAvatar=urlAvatar;
    this->role=role;
    this->isAuthenticated=isAuthenticated;
    this->groups=groups;
}

void Authentication::setIsAuthenticated(bool newIsAuthenticated)
{
    isAuthenticated = newIsAuthenticated;
}


void Authentication::setId(int32_t newId)
{
    id = newId;
}


int32_t Authentication::getId() const
{
    return id;
}

void Authentication::setPassword(const QString &newPassword)
{
    password = newPassword;
}

void Authentication::setFio(const QString &newFio)
{
    fio = newFio;
}

QList<QString> Authentication::getGroups() const
{
    return groups;
}


void Authentication::HashPassword()
{
    QByteArray salt,log;
    log=password.toUtf8()+"saLT";
    for(int i = 0; i<64;i+=3)
        salt.append(log[(i/3)%(log.size()-1)]);
    password=QPasswordDigestor::deriveKeyPbkdf2(QCryptographicHash::Algorithm::Sha3_512,log,salt,10000,64).toBase64();
    password=password.trimmed();
}

void Authentication:: SetInformationAfterAuthentication(
                                                  QString fio,
                                                  QString url_avatar,
                                                  EnumRoles role,

                                                  int32_t id, QList<QString> group){

    this->fio=fio;
    this->urlAvatar=url_avatar;
    this->role=role;
    this->id=id;
    this->isAuthenticated=true;
    this->groups=group;
}
QJsonObject Authentication:: Serialize() {
    QJsonObject json;
    json["login"]=login;
    json["password"]=password;
    json["fio"]=fio;
    json["id"]=id;
    json["urlAvatar"]=urlAvatar;
    json["role"]=role;
    json["isAuthenticated"]=isAuthenticated;
    QJsonArray gr;
    for(auto & g : groups)
        gr.append(g);
    json["groups"]=gr;
    return json;
}

Authentication* Authentication::Deserialize(QJsonObject jsonObj){
    QJsonArray gr=jsonObj["groups"].toArray();
    QList<QString> list;
    for(int i=0;i<gr.size();i++)
        list.append(gr[i].toString());
    return new Authentication(jsonObj["login"].toString(),jsonObj["password"].toString(),
                              jsonObj["id"].toInt(),jsonObj["fio"].toString(),
                              jsonObj["urlAvatar"].toString(), (EnumRoles)jsonObj["role"].toInt(),
                              list, jsonObj["isAuthenticated"].toBool());
}

