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
    explicit LoaderComponent(QWidget *parent = nullptr);
    ~LoaderComponent();

private:
    Ui::LoaderComponent *ui;
};

#endif // LOADERCOMPONENT_H
