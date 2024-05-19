#ifndef CHECKDZCOMPONENTS_H
#define CHECKDZCOMPONENTS_H

#include <QWidget>
#include "../../../../../common/transferEnum/transferEnum.h"
#include "../../../common/course/course_components/coursetask.h"
#include "../DzMarkEditer/dzmarkediter.h"
#include "../../../../../common/transferEnum/transferEnum.h"

namespace Ui {
class CheckDzComponents;
}

class CheckDzComponents : public QWidget
{
    Q_OBJECT

public:
    explicit CheckDzComponents(Submit* submit,QList<Submit*> submitList, QWidget *parent = nullptr);
    ~CheckDzComponents();

private slots:
    void on_pushButton_clicked();

private:
    Submit* sub;
    Ui::CheckDzComponents *ui;
    QList<Submit*> submitList;
};

#endif // CHECKDZCOMPONENTS_H
