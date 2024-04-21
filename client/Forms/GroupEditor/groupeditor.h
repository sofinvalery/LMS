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
    void on_addButton_clicked();
    void generateButton_clicked();
    void deleteButton_clicked();

private:
    int count = 0;
    int heightLine = 0;
    QList<QLineEdit*> nameList;
    QList<QPushButton*> deleteList;
    QList<QLabel*> numberList;
    Ui::groupEditor *ui;
};

#endif // GROUPEDITOR_H
