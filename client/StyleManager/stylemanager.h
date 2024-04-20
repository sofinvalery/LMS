#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QPushButton>
#include <QFontDatabase>
#include <QString>
#include <QGroupBox>
#include <QScreen>
#include <QLabel>
#include <QGuiApplication>
#include <QLineEdit>

class StyleManager
{
public:
    static StyleManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new StyleManager()); }
    static QFont getRegular();
    static QFont getBold();
    void setSimpleButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int fontSizeAnim);
    void setBlueButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int borderRadius);
    void setDisableButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int borderRadius);
    void setWidgetStyle(QWidget* widgetName, QGroupBox* groupboxName, unsigned short int moveY);
    void setGroupBoxStyle();
    void setLabelStyle(QLabel* labelName, QString labelText, bool boldStatus, QString textColour, bool hideStatus, unsigned short int fontSize);
    void setLineEditStyle(QLineEdit* lineEditName, QString placeHolderText, bool boldStatus, unsigned short int fontSize, unsigned short int W, unsigned short int H);

private:
    StyleManager();
    static StyleManager* s_Instance;
    QFont regularFont;
    QFont boldFont;
};

#endif // STYLEMANAGER_H
