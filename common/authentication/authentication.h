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
    explicit Authentication(QString login, QString password,QString fio="",QString urlAvatar="",
                            EnumRoles role=USER,bool isAuthenticated=false, QObject *parent = nullptr);
    //используется при преходе ответа с сервера и заполняет данные

signals:

private:
    QString login;
    QString password;
    QString fio;
    QString urlAvatar;
    EnumRoles role;
    bool isAuthenticated;
   public slots:
    void SetInformationAfterAuthentication(
        QString fio,
        QString url_avatar,
        EnumRoles role);
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
       QJsonObject Serialize();
       static Authentication* Deserialize(QJsonObject jsonObj);
};

#endif // AUTHENTICATION_H
