QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../common/authentication/authentication.cpp \
    ../common/course/course.cpp \
    ../common/course/course_components/coursepdf.cpp \
    ../common/course/course_components/coursetask.cpp \
    ../common/course/course_components/coursetest.cpp \
    ../common/course/course_components/coursetutorials.cpp \
    ClientManager/clientmanager.cpp \
    Forms/Auth/auth.cpp \
    Forms/Main/mainwindow.cpp \
    Forms/MyWidget/mywidget.cpp \
    main.cpp  \
    ../common/course/course_components/coursevideos.cpp \
    ../common/course/course_components/question.cpp

HEADERS += \
    ../common/authentication/authentication.h \
    ../common/course/course.h \
    ../common/course/course_components/coursecomponent.h \
    ../common/course/course_components/coursepdf.h \
    ../common/course/course_components/coursetask.h \
    ../common/course/course_components/coursetest.h \
    ../common/course/course_components/coursetutorials.h \
    ../common/transferEnum/transferEnum.h \
    ClientManager/clientmanager.h \
    Forms/Auth/auth.h \
    Forms/Main/mainwindow.h  \
    ../common/course/course_components/coursevideos.h \
    ../common/course/course_components/question.h \
    Forms/MyWidget/mywidget.h

FORMS += \
    Forms/Auth/auth.ui \
    Forms/Main/mainwindow.ui \
    Forms/MyWidget/mywidget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
