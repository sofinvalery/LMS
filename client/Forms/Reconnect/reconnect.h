#ifndef RECONNECT_H
#define RECONNECT_H

#include <QDialog>

namespace Ui {
class Reconnect;
}

class Reconnect : public QDialog
{
    Q_OBJECT

public:
    explicit Reconnect(QWidget *parent = nullptr);
    ~Reconnect();

private slots:
    void on_exitButton_clicked();
    void on_reconnectButton_clicked();
private:
    Ui::Reconnect *ui;
};

#endif // RECONNECT_H
