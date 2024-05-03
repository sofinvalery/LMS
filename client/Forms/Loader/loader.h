#ifndef LOADER_H
#define LOADER_H

#include <QDialog>
#include <QHash>
namespace Ui {
class Loader;
}

class Loader : public QDialog
{
    Q_OBJECT

public:
    explicit Loader(QWidget *parent = nullptr);
    ~Loader();
private slots:
    void createWidget(QString fileName, qint64 totalSize);
    void deleteWidget(QString fileName);
private:
    QHash<QString, QWidget*> widgetHash;
    int heightLine = 0;
    Ui::Loader *ui;
};

#endif // LOADER_H
