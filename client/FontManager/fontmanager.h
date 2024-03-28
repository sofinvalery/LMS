#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QFontDatabase>
#include <QFont>

class FontManager
{
public:
    static FontManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new FontManager()); }
    static QFont getRegular();
    static QFont getBold();
private:
    FontManager();
    static FontManager* s_Instance;
    QFont regularFont;
    QFont boldFont;
};

#endif // FONTMANAGER_H
