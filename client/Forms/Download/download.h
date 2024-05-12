#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QWidget>
#include <QMovie>

namespace Ui {
class Download;
}

class Download : public QWidget
{
    Q_OBJECT

public:
    explicit Download(QWidget *parent = nullptr);
    ~Download();

private:
    Ui::Download *ui;
};

#endif // DOWNLOAD_H
