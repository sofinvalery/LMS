#ifndef GENERATE_PASSWORD_H
#define GENERATE_PASSWORD_H
#include <QString>
#include <QRandomGenerator>
#include <QDateTime>

QList<QString> passwordRand(qint32 quantity,quint32 complexity)
{
    QRandomGenerator rand = QRandomGenerator(QDateTime::currentMSecsSinceEpoch());
    QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_&?!*^:;#%<>+=";
    QString password;
    QList<QString> list;
    int num;
    for(quint32 i =0;i<quantity;i++ ){
        for (quint32 i = 0; i < complexity; i++) {
            num = rand.bounded(chars.size());
            password += chars.at(num);
        }
        list.append(password);
        password="";
    }
    return list;
}


#endif // GENERATE_PASSWORD_H
