#ifndef COURSECOMPONENT_H
#define COURSECOMPONENT_H

#include "qobject.h"
#include <QObject>
#include<QTextEdit>

class CourseComponent : public QObject
{
    Q_OBJECT
public:
    explicit CourseComponent(int32_t id,int32_t order, QObject *parent = nullptr):QObject{parent}{
        this->id=id;
        this->order=order;
    }
    int32_t getOrder() const
    {
        return order;
    }
    int32_t getId(){
        return id;
    }
    virtual QJsonObject Serialize()=0;
protected:
    int32_t id;
    int32_t order;
public slots:
    virtual void ClickIcon()=0;
    virtual QWidget* QWidgetShow()=0;
signals:
};

#endif // COURSECOMPONENT_H
