QT += core
QT += network
QT += widgets
QT += sql
QT += concurrent
QTPLUGIN += QPSQL

CONFIG += c++17 cmdline console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../common/authentication/authentication.cpp \
        ../../common/authentication/group.cpp \
        ../../common/course/course.cpp \
        ../../common/course/course_components/coursepdf.cpp \
        ../../common/course/course_components/coursetask.cpp \
        ../../common/course/course_components/coursetest.cpp \
        ../../common/course/course_components/coursetutorials.cpp \
        ../../common/course/course_components/coursevideos.cpp \
        ../../common/course/course_components/question.cpp \
        database/databaseManager.cpp \
        database/requests.cpp \
        jsonManager/jsonmanager.cpp \
        main.cpp \
        server/client.cpp \
        server/myserver.cpp \
        server/servertask.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../common/authentication/authentication.h \
    ../../common/authentication/group.h \
    ../../common/course/course.h \
    ../../common/course/course_components/coursecomponent.h \
    ../../common/course/course_components/coursepdf.h \
    ../../common/course/course_components/coursetask.h \
    ../../common/course/course_components/coursetest.h \
    ../../common/course/course_components/coursetutorials.h \
    ../../common/course/course_components/coursevideos.h \
    ../../common/course/course_components/question.h \
    ../../common/transferEnum/transferEnum.h \
    database/databaseManager.h \
    jsonManager/jsonmanager.h \
    server/client.h \
    server/myserver.h \
    server/servertask.h

RESOURCES += \
    resources.qrc
macx {
    INCLUDEPATH += /Users/valeriysofin/Qt/6.6.3/macos/plugins/sqldrivers
    INCLUDEPATH += /Applications/Postgres.app/Contents/Versions/16/include
    INCLUDEPATH += /Applications/Postgres.app/Contents/Versions/16/lib
    LIBS += -L/usr/local/lib -lpq
    INCLUDEPATH += /usr/local/mysql-connector-cpp/include
    # LIBS += -L/usr/local/mysql-connector-cpp/lib -lmysqlcppconn
}




