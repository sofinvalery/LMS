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
#include <QScrollArea>
#include <QScrollBar>
#include <QCompleter>
#include <QAbstractItemView>
#include <QProgressBar>

class StyleManager
{
public:
    static StyleManager* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new StyleManager()); }
    static QFont getRegular();
    static QFont getBold();
    int getScreenWidth();
    int getScreenHeight();
    void setSimpleButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int fontSizeAnim);
    void setBlueButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int borderRadius);
    void setCustomButtonStyle(QPushButton* buttonName, QString buttonText, QString buttonColour, bool boldStatus, unsigned short int fontSize, unsigned short int borderRadius);
    void setDisableButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int borderRadius);
    void setWidgetStyle(QWidget* widgetName, QGroupBox* groupboxName, unsigned short int moveY = 90);
    void setGroupBoxStyle();
    void setLabelStyle(QLabel* labelName, QString labelText, bool boldStatus, QString textColour, bool showStatus, unsigned short int fontSize, bool backgroundColour = false, QString setBackgroundColour = "#82c7ff");
    void setLineEditStyle(QLineEdit* lineEditName, QString placeHolderText, bool boldStatus, unsigned short int fontSize, unsigned short int W, unsigned short int H);
    void setScrollAreaStyle(QScrollArea* scrollAreaName, bool topBorderStatus);
    void setLinkButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int fontSizeAnim);
    void setCompleterStyle(QCompleter* completerName, QString fontFamily = "Comfortaa");
    void setProgressBarStyle(QProgressBar* progressBarName, bool boldStatus, unsigned short int borderRadius = 10, QString backgroundColour = "lightgrey", QString downloadColour = "#4EB5FF");
private:
    QScreen* scr = QGuiApplication::primaryScreen();
    StyleManager();
    static StyleManager* s_Instance;
    QFont regularFont;
    QFont boldFont;
    QString adjustColour(const QString& colour, int delta);
};

#endif // STYLEMANAGER_H
