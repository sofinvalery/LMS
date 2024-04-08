#include "stylemanager.h"

StyleManager* StyleManager::s_Instance = nullptr;

StyleManager::StyleManager() {}

void StyleManager::setSimpleStyle(QPushButton* buttonName)
{
    buttonName->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 20px;"
        "}"
        "QPushButton:pressed {"
        "font-size: 18px;"
        "}");
}

void StyleManager::setBlueStyle(QPushButton* buttonName)
{
    buttonName->setStyleSheet(
        "QPushButton {"
        "background-color: #4AB8FF;"
        "border-radius: 13px;"
        "border: none;"
        "color: white;"
        "font-size: 20px;"
        "}"
        "QPushButton:hover {"
        "background-color: #2194DE;"
        "}"
        "QPushButton:pressed {"
        "background-color: #0E5FA8;"
        "}");
}
