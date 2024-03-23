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
QJsonObject Authentication:: SerializeForAuthentication(){
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
    json["tokenAuthentication"]=tokenAuthentication;

    return json;
}

void Authentication::DeserializeAfterAuthFromServer(QJsonObject jsonObj){
    this->fio=jsonObj["fio"].toString();
    this->urlAvatar=jsonObj["urlAvatar"].toString();
    this->role=(EnumRoles)jsonObj["role"].toInt();
    this->tokenAuthentication=jsonObj["tokenAuthentication"].toInt();
    this->isAuthenticated=true;
}

