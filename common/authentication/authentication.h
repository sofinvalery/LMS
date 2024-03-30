#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPasswordDigestor>
#include <QCryptographicHash>
#include <QJsonArray>

enum EnumRoles{
    ADMIN=0,
    STUDENT=1,
    TEACHER=2
};

class Authentication : public QObject
{
    Q_OBJECT
public:

    /*Создается при входе на портал выступает для аутенфикации*/
    explicit Authentication(QString login, QString password,int32_t id=0,QString fio="",QString urlAvatar="",
                            EnumRoles role=STUDENT, QList<QString> groups=QList<QString>(), bool isAuthenticated=false, QObject *parent = nullptr);
    //используется при преходе ответа с сервера и заполняет данные

    void setIsAuthenticated(bool newIsAuthenticated);

    void setId(int32_t newId);


    int32_t getId() const;

signals:

private:
    QString login;
    QString password;
    QString fio;
    QString urlAvatar;
    EnumRoles role;
    bool isAuthenticated;
    int32_t id;
    QList<QString> groups;

   public slots:
    void SetInformationAfterAuthentication(
        QString fio,
        QString url_avatar,
        EnumRoles role,
        int32_t id,
        QList<QString> groups);

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

       QString GetLogin() { return login; }

       QString GetPassword() { return password; }

       QJsonObject Serialize();
       static Authentication* Deserialize(QJsonObject jsonObj);
};

#endif // AUTHENTICATION_H
