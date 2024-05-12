#ifndef LOADERCOMPONENT_H
#define LOADERCOMPONENT_H

#include <QWidget>

namespace Ui {
class LoaderComponent;
}

class LoaderComponent : public QWidget
{
    Q_OBJECT

public:
    explicit LoaderComponent(QWidget *parent = nullptr, QString fileName = "fileName", qint64 totalSize = 100000);
    ~LoaderComponent();
private slots:
    void increaseDownload(qint64 newValue);
private:
    qint64 currentDownload = 0;
    Ui::LoaderComponent *ui;
};

#endif // LOADERCOMPONENT_H
