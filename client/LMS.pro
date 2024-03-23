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
<<<<<<< HEAD
    Forms/Auth/auth.cpp \
    Forms/Main/mainwindow.cpp \
    main.cpp
=======
    ../common/course/course_components/coursevideos.cpp \
    ../common/course/course_components/question.cpp \
    main.cpp \
    mainwindow.cpp
>>>>>>> 890d1dfa3f50add1f2a65f8b38f17ded7f5af4b7

HEADERS += \
    ../common/authentication/authentication.h \
    ../common/course/course.h \
    ../common/course/course_components/coursecomponent.h \
    ../common/course/course_components/coursepdf.h \
    ../common/course/course_components/coursetask.h \
    ../common/course/course_components/coursetest.h \
    ../common/course/course_components/coursetutorials.h \
<<<<<<< HEAD
    Forms/Auth/auth.h \
    Forms/Main/mainwindow.h
=======
    ../common/course/course_components/coursevideos.h \
    ../common/course/course_components/question.h \
    mainwindow.h
>>>>>>> 890d1dfa3f50add1f2a65f8b38f17ded7f5af4b7

FORMS += \
    Forms/Auth/auth.ui \
    Forms/Main/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
