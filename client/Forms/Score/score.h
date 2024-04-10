#ifndef SCORE_H
#define SCORE_H

#include <QWidget>

namespace Ui {
class Score;
}

class Score : public QWidget
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = nullptr);
    ~Score();

private:
    Ui::Score *ui;
};

#endif // SCORE_H
