#include "generate_password.h"

QList<QString> passwordRand(qint32 quantity,quint32 complexity)
{
    QRandomGenerator *rand =  QRandomGenerator::system();
    QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    QString password;
    QList<QString> list;
    int num;
    for(quint32 i =0;i<quantity;i++ ){
        for (quint32 i = 0; i < complexity; i++) {
            num = rand->bounded(chars.size());
            password += chars.at(num);
        }
        list.append(password);
        password="";
    }
    return list;
}
