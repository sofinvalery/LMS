#ifndef CHECKDZ_H
#define CHECKDZ_H

#include <QWidget>
#include "../../../../common/transferEnum/transferEnum.h"
#include "CheckDzComponents/checkdzcomponents.h"

namespace Ui {
class CheckDz;
}

class CheckDz : public QWidget
{
    Q_OBJECT

public:
    explicit CheckDz(QList<Submit*> submitList, QWidget *parent = nullptr);
    ~CheckDz();

private slots:
    void on_exitButton_clicked();

private:
    int HeightLine = 20;
    Ui::CheckDz *ui;
};

#endif // CHECKDZ_H
