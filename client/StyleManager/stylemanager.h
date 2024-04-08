#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QPushButton>

class StyleManager
{
public:
    static StyleManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new StyleManager()); }
    static void setSimpleStyle(QPushButton* buttonName);
    static void setBlueStyle(QPushButton* buttonName);
    StyleManager();
private:
    static StyleManager* s_Instance;
};

#endif // STYLEMANAGER_H
