QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../common/authentication/authentication.cpp \
    ../common/authentication/group.cpp \
    ../common/course/course.cpp \
    ../common/course/course_components/coursepdf.cpp \
    ../common/course/course_components/coursetask.cpp \
    ../common/course/course_components/coursetest.cpp \
    ../common/course/course_components/coursetutorials.cpp \
    ClientManager/clientmanager.cpp \
    ClientManager/socketparser.cpp \
    ClientState/clientstate.cpp \
    Forms/AddGroup/addgroup.cpp \
    Forms/Auth/auth.cpp \
    Forms/CourseAdder/courseadder.cpp \
    Forms/CoursePage/AdminScore/adminscore.cpp \
    Forms/CoursePage/CoursePageEditor/coursepageeditor.cpp \
    Forms/CoursePage/coursepage.cpp \
    Forms/CoursePageComponents/CourseAttestacion/courseattestacion.cpp \
    Forms/CoursePageComponents/CourseDownload/coursedownload.cpp \
    Forms/CoursePageComponents/CourseDz/coursedz.cpp \
    Forms/CoursePageComponents/CourseText/coursetext.cpp \
    Forms/CoursesMPWidget/coursesmpwidget.cpp \
    Forms/Download/download.cpp \
    Forms/GroupEditor/groupeditor.cpp \
    Forms/Loader/LoaderComponent/loadercomponent.cpp \
    Forms/Loader/loader.cpp \
    Forms/Main/mainwindow.cpp \
    Forms/MyWidget/mywidget.cpp \
    Forms/Notification/notification.cpp \
    Forms/PotokAdder/potokadder.cpp \
    Forms/Profile/profile.cpp \
    Forms/Reconnect/reconnect.cpp \
    Forms/Score/ScoreComponents/scorecomponents.cpp \
    Forms/Score/TestTaskComponents/testtaskcomponents.cpp \
    Forms/Score/score.cpp \
    Forms/TestWidget/TestEditor/testeditor.cpp \
    Forms/TestWidget/testwidget.cpp \
    StyleManager/stylemanager.cpp \
    main.cpp  \
    ../common/course/course_components/coursevideos.cpp \
    ../common/course/course_components/question.cpp

HEADERS += \
    ../common/authentication/authentication.h \
    ../common/authentication/group.h \
    ../common/course/course.h \
    ../common/course/course_components/coursecomponent.h \
    ../common/course/course_components/coursepdf.h \
    ../common/course/course_components/coursetask.h \
    ../common/course/course_components/coursetest.h \
    ../common/course/course_components/coursetutorials.h \
    ../common/transferEnum/transferEnum.h \
    ClientManager/clientmanager.h \
    ClientManager/socketparser.h \
    ClientState/clientstate.h \
    Forms/AddGroup/addgroup.h \
    Forms/Auth/auth.h \
    Forms/CourseAdder/courseadder.h \
    Forms/CoursePage/AdminScore/adminscore.h \
    Forms/CoursePage/CoursePageEditor/coursepageeditor.h \
    Forms/CoursePage/coursepage.h \
    Forms/CoursePageComponents/CourseAttestacion/courseattestacion.h \
    Forms/CoursePageComponents/CourseDownload/coursedownload.h \
    Forms/CoursePageComponents/CourseDz/coursedz.h \
    Forms/CoursePageComponents/CourseText/coursetext.h \
    Forms/CoursePageComponents/componentswidgetfactory.h \
    Forms/CoursesMPWidget/coursesmpwidget.h \
    Forms/Download/download.h \
    Forms/GroupEditor/groupeditor.h \
    Forms/Loader/LoaderComponent/loadercomponent.h \
    Forms/Loader/loader.h \
    Forms/Main/mainwindow.h  \
    ../common/course/course_components/coursevideos.h \
    ../common/course/course_components/question.h \
    Forms/MyWidget/mywidget.h \
    Forms/Notification/notification.h \
    Forms/PotokAdder/potokadder.h \
    Forms/Profile/profile.h \
    Forms/Reconnect/reconnect.h \
    Forms/Score/ScoreComponents/scorecomponents.h \
    Forms/Score/TestTaskComponents/testtaskcomponents.h \
    Forms/Score/score.h \
    Forms/TestWidget/TestEditor/testeditor.h \
    Forms/TestWidget/testwidget.h \
    StyleManager/stylemanager.h

FORMS += \
    Forms/AddGroup/addgroup.ui \
    Forms/Auth/auth.ui \
    Forms/CourseAdder/courseadder.ui \
    Forms/CoursePage/AdminScore/adminscore.ui \
    Forms/CoursePage/CoursePageEditor/coursepageeditor.ui \
    Forms/CoursePage/coursepage.ui \
    Forms/CoursePageComponents/CourseAttestacion/courseattestacion.ui \
    Forms/CoursePageComponents/CourseDownload/coursedownload.ui \
    Forms/CoursePageComponents/CourseDz/coursedz.ui \
    Forms/CoursePageComponents/CourseText/coursetext.ui \
    Forms/CoursesMPWidget/coursesmpwidget.ui \
    Forms/Download/download.ui \
    Forms/GroupEditor/groupeditor.ui \
    Forms/Loader/LoaderComponent/loadercomponent.ui \
    Forms/Loader/loader.ui \
    Forms/Main/mainwindow.ui \
    Forms/MyWidget/mywidget.ui \
    Forms/Notification/notification.ui \
    Forms/PotokAdder/potokadder.ui \
    Forms/Profile/profile.ui \
    Forms/Reconnect/reconnect.ui \
    Forms/Score/ScoreComponents/scorecomponents.ui \
    Forms/Score/TestTaskComponents/testtaskcomponents.ui \
    Forms/Score/score.ui \
    Forms/TestWidget/TestEditor/testeditor.ui \
    Forms/TestWidget/testwidget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
