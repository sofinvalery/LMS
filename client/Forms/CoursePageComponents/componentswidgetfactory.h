#ifndef COMPONENTSWIDGETFACTORY_H
#define COMPONENTSWIDGETFACTORY_H

#include <QObject>
#include <Qmap>
#include "CourseDownload/coursedownload.h"
#include "CourseAttestacion/courseattestacion.h"
#include "CourseText/coursetext.h"
#include "CourseDz/coursedz.h"

template<class ID,class Base,class ... Args> class ComponentsWidgetFactory : public QObject
{
public:
    explicit ComponentsWidgetFactory(QObject *parent = nullptr){init();}
private:
    typedef Base* (*fInstantiator)(Args ...);

    template<class Derived> static Base* instantiator(Args ... args){
        return new Derived(args ...);
    }
    void init()
    {
        add<CourseDownload>("CourseMediaFiles");
        add<CourseDz>("CourseTask");
        add<CourseText>("CourseTutorials");
        add<CourseAttestacion>("CourseTest");
    }
    template<class Derived> void add(ID id){
        classes[id]=&instantiator<Derived>;
    }
    QMap<ID,fInstantiator> classes;
public:

    fInstantiator get(ID id){
        return classes[id];
    }
signals:
};

#endif // COMPONENTSWIDGETFACTORY_H
