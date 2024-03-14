#include "authentication.h"

Authentication::Authentication(QString login,QString password, QObject *parent): QObject{parent}
{
    this->login=login;
    this->password=password;
    this->isAuthenticated=false;
}
void Authentication:: SetInformationAfterAuthentication(
                                                  QString fio,
                                                  QString url_avatar,
                                                  EnumRoles role,
                                                  int32_t token_authentication){
    this->fio=fio;
    this->urlAvatar=url_avatar;
    this->role=role;
    this->tokenAuthentication=token_authentication;
    this->isAuthenticated=true;
}
QString Authentication:: SerializeForAuthentication(){
    QJsonObject json;
    json["login"]=login;
    json["password"]=password;
    QJsonDocument doc(json);
    QString jsonString = doc.toJson();
    return jsonString;
}

void Authentication::DeserializeAfterAuthFromServer(QString jsonString){
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = doc.object();
    this->fio=jsonObj["fio"].toString();
    this->urlAvatar=jsonObj["urlAvatar"].toString();
    this->role=(EnumRoles)jsonObj["role"].toInt();
    this->tokenAuthentication=jsonObj["tokenAuthentication"].toInt();
    this->isAuthenticated=true;
}

