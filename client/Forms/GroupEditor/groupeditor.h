#ifndef GROUPEDITOR_H
#define GROUPEDITOR_H

#include <QWidget>
#include <StyleManager/stylemanager.h>
#include <QList>

namespace Ui {
class groupEditor;
}

class groupEditor : public QWidget
{
    Q_OBJECT

public:
    explicit groupEditor(QWidget *parent = nullptr);
    ~groupEditor();

signals:
    void generateButtonClicked();
    void deleteButtonClicked();

private slots:
    void on_showGroupButton_clicked();
    void on_addButton_clicked(); //добавить нового чела
    void generateButton_clicked(); //пароль
    void deleteButton_clicked(); //удалить
    void on_createButton_clicked(); //применить

private:
    int heightLine = 0;
    QList<QLineEdit*> nameList; //список фио
    Ui::groupEditor *ui;
};

#endif // GROUPEDITOR_H
