#include "authentication.h"


Authentication::Authentication(QString login, QString password, QString fio, QString urlAvatar,
                               EnumRoles role,bool isAuthenticated, QObject *parent):QObject(parent)
{
    this->login=login;
    this->password=password;
    this->fio=fio;
    this->urlAvatar=urlAvatar;
    this->role=role;
    this->isAuthenticated=isAuthenticated;
}

void Authentication:: SetInformationAfterAuthentication(
                                                  QString fio,
                                                  QString url_avatar,
                                                  EnumRoles role){
    this->fio=fio;
    this->urlAvatar=url_avatar;
    this->role=role;
    this->isAuthenticated=true;
}
QJsonObject Authentication:: Serialize(){
    QJsonObject json;
    json["login"]=login;
    QByteArray salt,log;
    log=password.toUtf8();
    for(int i = 0; i<64;i+=3)
        salt.append(log[(i/3)%(log.size()-1)]);
    json["password"]=(QString)QPasswordDigestor::deriveKeyPbkdf2(QCryptographicHash::Algorithm::Sha3_512,log,salt,10000,64);
    json["fio"]=fio;
    json["urlAvatar"]=urlAvatar;
    json["role"]=role;
    json["isAuthenticated"]=isAuthenticated;
    return json;
}

Authentication* Authentication::Deserialize(QJsonObject jsonObj){
    return new Authentication(jsonObj["login"].toString(),jsonObj["password"].toString(),
                              jsonObj["fio"].toString(),jsonObj["urlAvatar"].toString(),
                              (EnumRoles)jsonObj["role"].toInt(),jsonObj["isAuthenticated"].toBool());
}

