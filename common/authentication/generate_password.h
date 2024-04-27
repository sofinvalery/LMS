#ifndef GENERATE_PASSWORD_H
#define GENERATE_PASSWORD_H
#include <QString>
#include <QRandomGenerator>
#include <QDateTime>

QList<QString> passwordRand(qint32 quantity,quint32 complexity);


#endif // GENERATE_PASSWORD_H
