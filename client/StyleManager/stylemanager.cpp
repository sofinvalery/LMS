#include "stylemanager.h"

StyleManager* StyleManager::s_Instance = nullptr;

StyleManager::StyleManager() {
    QFontDatabase::addApplicationFont(":/font/resources/Comfortaa-Regular.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/Comfortaa-Bold.ttf");

    regularFont.setFamily("Comfortaa");
    regularFont.setWeight(QFont::Normal);

    boldFont.setFamily("Comfortaa");
    boldFont.setWeight(QFont::Bold);
}

void StyleManager::setSimpleButtonStyle(QPushButton* buttonName, QString buttonText, QString fontWeight, unsigned short int fontSize, unsigned short int fontSizeAnim = 18)
{
    if (fontWeight == "regular")
    {
        regularFont.setPixelSize(fontSize);
        buttonName->setFont(regularFont);
    }
    else if (fontWeight == "bold")
    {
        boldFont.setPixelSize(fontSize);
        buttonName->setFont(boldFont);
    }
    buttonName->setCursor(Qt::PointingHandCursor);
    buttonName->setText(buttonText);
    buttonName->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "}"
        "QPushButton:pressed {"
        "font-size: " + QString::number(fontSizeAnim) + "px;"
        "}");
}

void StyleManager::setBlueButtonStyle(QPushButton* buttonName, QString buttonText, QString fontWeight, unsigned short int fontSize, unsigned short int borderRadius = 10)
{
    if (fontWeight == "regular")
    {
        regularFont.setPixelSize(fontSize);
        buttonName->setFont(regularFont);
    }
    else if (fontWeight == "bold")
    {
        boldFont.setPixelSize(fontSize);
        buttonName->setFont(boldFont);
    }
    buttonName->setCursor(Qt::PointingHandCursor);
    buttonName->setText(buttonText);
    buttonName->setStyleSheet(
        "QPushButton {"
        "background-color: #4AB8FF;"
        "border-radius: " + QString::number(borderRadius) + "px;"
        "border: none;"
        "color: white;"
        "}"
        "QPushButton:hover {"
        "background-color: #2194DE;"
        "}"
        "QPushButton:pressed {"
        "background-color: #0E5FA8;"
        "}");
}

void StyleManager::setDisableButtonStyle(QPushButton* buttonName, QString buttonText, QString fontWeight, unsigned short int fontSize, unsigned short int borderRadius = 10)
{
    if (fontWeight == "regular")
    {
        regularFont.setPixelSize(fontSize);
        buttonName->setFont(regularFont);
    }
    else if (fontWeight == "bold")
    {
        boldFont.setPixelSize(fontSize);
        buttonName->setFont(boldFont);
    }
    buttonName->setText(buttonText);
    buttonName->setStyleSheet(
        "QPushButton {"
        "background-color: lightgrey;"
        "border-radius: " + QString::number(borderRadius) + "px;"
        "border: none;"
        "color: grey;"
        "}");
}

QFont StyleManager::getRegular()
{
    return GetInstance()->regularFont;
}

QFont StyleManager::getBold()
{
    return GetInstance()->boldFont;
}
