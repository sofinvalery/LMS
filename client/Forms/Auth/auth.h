#ifndef AUTH_H
#define AUTH_H

#include <QDialog>
#include "FontManager/fontmanager.h"
#include "../common/authentication/authentication.h"
#include "ClientManager/socketparser.h"
#include "ClientManager/clientmanager.h"
#include "QJsonObject"
#include "../common/transferEnum/transferEnum.h"
#include "ClientState/clientstate.h"
#include "Forms/Main/mainwindow.h"

namespace Ui {
class Auth;
}

class Auth : public QDialog
{
    Q_OBJECT

public:
    explicit Auth(QWidget *parent = nullptr);
    int authstatus = -1;
    bool exit = false;
    ~Auth();

private slots:
    void on_pushButton_clicked();
    void showMainPage();
private:
    Ui::Auth *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // AUTH_H
