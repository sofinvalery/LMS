#ifndef AUTH_H
#define AUTH_H

#include <QDialog>

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

    void on_Auth_rejected();

private:
    Ui::Auth *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // AUTH_H
