#include "fontmanager.h"

FontManager* FontManager::s_Instance = nullptr;

FontManager::FontManager()
{
    QFontDatabase::addApplicationFont(":/font/resources/Comfortaa-Regular.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/Comfortaa-Bold.ttf");
    regularFont.setFamily("Comfortaa");

    regularFont.setWeight(QFont::Normal);
    boldFont.setFamily("Comfortaa");
    boldFont.setWeight(QFont::Bold);
}

QFont FontManager::getRegular()
{
    return GetInstance()->regularFont;
}

QFont FontManager::getBold()
{
    return GetInstance()->boldFont;
}
