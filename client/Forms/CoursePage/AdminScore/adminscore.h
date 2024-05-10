#ifndef ADMINSCORE_H
#define ADMINSCORE_H

#include <QWidget>

namespace Ui {
class AdminScore;
}

class AdminScore : public QWidget
{
    Q_OBJECT

public:
    explicit AdminScore(QWidget *parent = nullptr);
    ~AdminScore();

private slots:
    void on_exitButton_clicked();

    void on_getCheckBox_clicked();

    void on_updateCheckBox_clicked();

    void on_getDoneButton_clicked();

    void on_getPatternButton_clicked();

    void on_setExcelButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::AdminScore *ui;
};

#endif // ADMINSCORE_H
