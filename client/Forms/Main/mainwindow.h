#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< Updated upstream
=======
#include "Forms/MyWidget/mywidget.h"

>>>>>>> Stashed changes
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    MyWidget * course[25];
};
#endif // MAINWINDOW_H
