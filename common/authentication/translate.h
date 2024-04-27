#ifndef TRANSLATE_H
#define TRANSLATE_H
#include <QString>
#include <QHash>

static QHash <QString,QString> toTranslit{
    {{"а", "a"},{"б", "b"},{"в", "v"},{"г", "g"},{"д", "d"},{"е", "e"},{"ё", "e"},{"ж", "j"},{"з", "z"},{"и", "i"},
    {"й", "i"},{"к", "k"},{"л", "l"},{"м", "m"},{"н", "h"},{"о", "o"},{"п", "p"},{"р", "r"},{"с", "s"},{"т", "t"},
    {"у", "u"},{"ф", "f"},{"х", "x"},{"ц", "c"},{"ч", "ch"},{"ш", "sh"},{"щ", "shch"},{"ъ", ""},{"ы", "iu"},{"ь", ""},
     {"э", "a"},{"ю", "iu"},{"я", "ia"}}

    };
QString translate(QString name);



#endif // TRANSLATE_H
