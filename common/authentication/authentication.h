#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPasswordDigestor>
#include <QCryptographicHash>


enum EnumRoles{
    ADMIN=0,
    USER=1,
    TEACHER=2
};

class Authentication : public QObject
{
    Q_OBJECT
public:
    /*Создается при входе на портал выступает для аутенфикации*/
    explicit Authentication(QString login, QString password,QObject *parent = nullptr);
    //используется при преходе ответа с сервера и заполняет данные

signals:

private:
    QString login;
    QString password;
    QString fio;
    QString urlAvatar;
    EnumRoles role;
    int32_t tokenAuthentication;
    bool isAuthenticated;
   public slots:
    void SetInformationAfterAuthentication(
        QString fio,
        QString url_avatar,
        EnumRoles role,
        int32_t token_authentication);
       bool IsAuthenticated(){
           return isAuthenticated;
       }
       EnumRoles GetCurrentRole(){
           return role;
       }
       QString GetFIO(){
           return fio;
       }
       QString GetUrlAvatar(){
           return urlAvatar;
       }
       QJsonObject SerializeForAuthentication();
       void DeserializeAfterAuthFromServer(QJsonObject jsonObj);
};

#endif // AUTHENTICATION_H
