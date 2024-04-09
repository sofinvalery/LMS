#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QPushButton>
#include <QFontDatabase>
#include <QString>

class StyleManager
{
public:
    static StyleManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new StyleManager()); }
    void setSimpleButtonStyle(QPushButton* buttonName, QString buttonText, QString fontWeight, unsigned short int fontSize, unsigned short int fontSizeAnim);
    void setBlueButtonStyle(QPushButton* buttonName, QString buttonText, QString fontWeight, unsigned short int fontSize, unsigned short int borderRadius);
private:
    StyleManager();
    static StyleManager* s_Instance;
    QFont regularFont;
    QFont boldFont;
};

#endif // STYLEMANAGER_H
