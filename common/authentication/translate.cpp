#include "translate.h"


QString translate(QString name)
{
    name = name.toLower();
    for(int j=0;j<name.size();j++)
    {
        QHash<QString,QString>::const_iterator i =toTranslit.find(name[j]);
        if(i!=toTranslit.end())
            name.replace(j,i.value().size(),i.value());
    }
    return name;
}
