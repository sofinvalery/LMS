#ifndef LOADER_H
#define LOADER_H

#include <QDialog>

namespace Ui {
class Loader;
}

class Loader : public QDialog
{
    Q_OBJECT

public:
    explicit Loader(QWidget *parent = nullptr);
    ~Loader();

private:
    int heightLine = 0;
    Ui::Loader *ui;
};

#endif // LOADER_H
