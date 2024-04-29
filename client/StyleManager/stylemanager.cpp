#include "stylemanager.h"

StyleManager* StyleManager::s_Instance = nullptr;

StyleManager::StyleManager() {
    QFontDatabase::addApplicationFont(":/font/resources/Comfortaa-Regular.ttf");
    QFontDatabase::addApplicationFont(":/font/resources/Comfortaa-Bold.ttf");

    regularFont.setFamily("Comfortaa");
    regularFont.setWeight(QFont::Normal);
    regularFont.setPixelSize(16);

    boldFont.setFamily("Comfortaa");
    boldFont.setWeight(QFont::Bold);
    boldFont.setPixelSize(16);
}

void StyleManager::setSimpleButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int fontSizeAnim = 18)
{
    buttonName->setFont(boldStatus == true ? StyleManager::GetInstance()->getBold() : StyleManager::GetInstance()->getRegular());
    buttonName->setCursor(Qt::PointingHandCursor);
    buttonName->setText(buttonText);
    buttonName->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: " + QString::number(fontSize) + "px;"
        "}"
        "QPushButton:pressed {"
        "font-size: " + QString::number(fontSizeAnim) + "px;"
        "}");
}

void StyleManager::setBlueButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int borderRadius = 10)
{
    buttonName->setFont(boldStatus == true ? StyleManager::GetInstance()->getBold() : StyleManager::GetInstance()->getRegular());
    buttonName->setCursor(Qt::PointingHandCursor);
    buttonName->setText(buttonText);
    buttonName->setStyleSheet(
        "QPushButton {"
        "background-color: #4AB8FF;"
        "border-radius: " + QString::number(borderRadius) + "px;"
        "font-size: " + QString::number(fontSize) + "px;"
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

void StyleManager::setDisableButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int borderRadius = 10)
{
    buttonName->setFont(boldStatus == true ? StyleManager::GetInstance()->getBold() : StyleManager::GetInstance()->getRegular());
    buttonName->setText(buttonText);
    buttonName->setStyleSheet(
        "QPushButton {"
        "background-color: lightgrey;"
        "border-radius: " + QString::number(borderRadius) + "px;"
        "font-size: " + QString::number(fontSize) + "px;"
        "border: none;"
        "color: grey;"
        "}");
}

void StyleManager::setWidgetStyle(QWidget* widgetName, QGroupBox* groupboxName, unsigned short int moveY)
{
    groupboxName->setStyleSheet(
        "QGroupBox {"
        "border-top: 3px solid lightgrey;"
        "}");
    widgetName->resize(scr->availableGeometry().width(), scr->availableGeometry().height() - 20);
    groupboxName->setMinimumSize(widgetName->frameGeometry().width(),widgetName->frameGeometry().height() - 20);
    widgetName->move(0, moveY);
}

void StyleManager::setLabelStyle(QLabel* labelName, QString labelText, bool boldStatus, QString textColour, bool showStatus, unsigned short int fontSize)
{
    labelName->setFont(boldStatus == true ? StyleManager::GetInstance()->getBold() : StyleManager::GetInstance()->getRegular());
    labelName->setVisible(showStatus);
    labelName->setText(labelText);
    labelName->setStyleSheet(
        "QLabel {"
        "font-size: " + QString::number(fontSize) + "px;"
        "color: " + textColour + ";"
        "}");
}

void StyleManager::setLineEditStyle(QLineEdit* lineEditName, QString placeHolderText, bool boldStatus, unsigned short int fontSize, unsigned short int W = 100, unsigned short int H = 50)
{
    lineEditName->setFont(boldStatus == true ? StyleManager::GetInstance()->getBold() : StyleManager::GetInstance()->getRegular());
    lineEditName->setPlaceholderText(placeHolderText);
    lineEditName->setFixedWidth(W);
    lineEditName->setFixedHeight(H);
    lineEditName->setStyleSheet(
        "QLineEdit {"
        "border: none;"
        "font-size: " + QString::number(fontSize) + "px;"
        "border-bottom: 2px solid lightgrey;"
        "}"
        );
}

void StyleManager::setScrollAreaStyle(QScrollArea* scrollAreaName, bool topBorderStatus)
{
    scrollAreaName->setStyleSheet(topBorderStatus ? "QScrollArea {"
                                                    "border: none;"
                                                    "border-top: 3px solid lightgrey;"
                                                    "}"
                                                  : "border: none;");
    scrollAreaName->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #F0F0F0;"
        "    width: 10px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #C0C0C0;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;"
        "}");
}

void StyleManager::setLinkButtonStyle(QPushButton* buttonName, QString buttonText, bool boldStatus, unsigned short int fontSize, unsigned short int fontSizeAnim)
{
    buttonName->setFont(boldStatus == true ? StyleManager::GetInstance()->getBold() : StyleManager::GetInstance()->getRegular());
    buttonName->setCursor(Qt::PointingHandCursor);
    buttonName->setText(buttonText);
        buttonName->setFixedSize(buttonName->sizeHint().width(), buttonName->sizeHint().height());
    buttonName->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: " + QString::number(fontSize) + "px;"
        "}"
        "QPushButton:hover {"
        "text-decoration: underline;"
        "color: purple;"
        "}"
        "QPushButton:pressed {"
        "font-size: " + QString::number(fontSizeAnim) + "px;"
        "}");
}

void StyleManager::setCustomButtonStyle(QPushButton* buttonName, QString buttonText, QString buttonColour, bool boldStatus, unsigned short int fontSize, unsigned short int borderRadius)
{
    buttonName->setFont(boldStatus == true ? StyleManager::GetInstance()->getBold() : StyleManager::GetInstance()->getRegular());
    buttonName->setCursor(Qt::PointingHandCursor);
    buttonName->setText(buttonText);
    buttonName->setStyleSheet(
        "QPushButton {"
        "background-color: " + buttonColour + ";"
        "border-radius: " + QString::number(borderRadius) + "px;"
        "font-size: " + QString::number(fontSize) + "px;"
        "border: none;"
        "color: white;"
        "}"
        "QPushButton:hover {"
        "background-color: " + adjustColour(buttonColour, -50) + ";"
        "}"
        "QPushButton:pressed {"
        "background-color: " + adjustColour(buttonColour, -80) + ";"
        "}");
}

void StyleManager::setCompleterStyle(QCompleter* completerName, QString fontFamily)
{
    completerName->popup()->setStyleSheet(
        "QListView {"
        "border: 2px solid lightgrey;"
        "font-family: " + fontFamily + ";"
        "}"
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #F0F0F0;"
        "    width: 10px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #C0C0C0;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;"
        "}");
}

QString StyleManager::adjustColour(const QString& colour, int delta) {
    QColor originalColour(colour);
    int h, s, v;
    originalColour.getHsv(&h, &s, &v);
    v = qBound(0, v + delta, 255);
    return QColor::fromHsv(h, s, v).name();
}

int StyleManager::getScreenWidth()
{
    return scr->availableGeometry().width();
}

int StyleManager::getScreenHeight()
{
    return scr->availableGeometry().height();
}

QFont StyleManager::getRegular()
{
    return GetInstance()->regularFont;
}

QFont StyleManager::getBold()
{
    return GetInstance()->boldFont;
}
