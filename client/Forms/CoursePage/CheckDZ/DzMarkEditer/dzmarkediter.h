#ifndef DZMARKEDITER_H
#define DZMARKEDITER_H

#include <QWidget>
#include "../../../../../common/transferEnum/transferEnum.h"
#include "../../../common/course/course_components/coursetask.h"

namespace Ui {
class DzMarkEditer;
}

class DzMarkEditer : public QWidget
{
    Q_OBJECT

public:
    explicit DzMarkEditer(Submit* submit, QWidget *parent = nullptr);
    ~DzMarkEditer();

private slots:
    void on_exitButton_clicked();

    void on_excelButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::DzMarkEditer *ui;
};

#endif // DZMARKEDITER_H
