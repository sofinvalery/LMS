cmake_minimum_required(VERSION 3.16)
project(LMS VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

qt_add_executable(LMS WIN32 MACOSX_BUNDLE
    ../common/authentication/authentication.cpp ../common/authentication/authentication.h
    ../common/authentication/generate_password.cpp ../common/authentication/generate_password.h
    ../common/authentication/group.cpp ../common/authentication/group.h
    ../common/authentication/translate.cpp ../common/authentication/translate.h
    ../common/course/course.cpp ../common/course/course.h
    ../common/course/course_components/coursecomponent.h
    ../common/course/course_components/coursemediafiles.cpp ../common/course/course_components/coursemediafiles.h
    ../common/course/course_components/coursetask.cpp ../common/course/course_components/coursetask.h
    ../common/course/course_components/coursetest.cpp ../common/course/course_components/coursetest.h
    ../common/course/course_components/coursetutorials.cpp ../common/course/course_components/coursetutorials.h
    ../common/course/course_components/question.cpp ../common/course/course_components/question.h
    ../common/transferEnum/transferEnum.h
    ClientManager/clientmanager.cpp ClientManager/clientmanager.h
    ClientManager/socketparser.cpp ClientManager/socketparser.h
    ClientState/clientstate.cpp ClientState/clientstate.h
    Forms/AddGroup/addgroup.cpp Forms/AddGroup/addgroup.h Forms/AddGroup/addgroup.ui
    Forms/Auth/auth.cpp Forms/Auth/auth.h Forms/Auth/auth.ui
    Forms/CourseAdder/courseadder.cpp Forms/CourseAdder/courseadder.h Forms/CourseAdder/courseadder.ui
    Forms/CoursePage/AdminScore/adminscore.cpp Forms/CoursePage/AdminScore/adminscore.h Forms/CoursePage/AdminScore/adminscore.ui
    Forms/CoursePage/CoursePageEditor/coursepageeditor.cpp Forms/CoursePage/CoursePageEditor/coursepageeditor.h Forms/CoursePage/CoursePageEditor/coursepageeditor.ui
    Forms/CoursePage/coursepage.cpp Forms/CoursePage/coursepage.h Forms/CoursePage/coursepage.ui
    Forms/CoursePageComponents/CourseAttestacion/courseattestacion.cpp Forms/CoursePageComponents/CourseAttestacion/courseattestacion.h Forms/CoursePageComponents/CourseAttestacion/courseattestacion.ui
    Forms/CoursePageComponents/CourseDownload/coursedownload.cpp Forms/CoursePageComponents/CourseDownload/coursedownload.h Forms/CoursePageComponents/CourseDownload/coursedownload.ui
    Forms/CoursePageComponents/CourseDz/CourseDzPage/coursedzpage.cpp Forms/CoursePageComponents/CourseDz/CourseDzPage/coursedzpage.h Forms/CoursePageComponents/CourseDz/CourseDzPage/coursedzpage.ui
    Forms/CoursePageComponents/CourseDz/coursedz.cpp Forms/CoursePageComponents/CourseDz/coursedz.h Forms/CoursePageComponents/CourseDz/coursedz.ui
    Forms/CoursePageComponents/CourseText/coursetext.cpp Forms/CoursePageComponents/CourseText/coursetext.h Forms/CoursePageComponents/CourseText/coursetext.ui
    Forms/CoursePageComponents/componentswidgetfactory.h
    Forms/CoursesMPWidget/coursesmpwidget.cpp Forms/CoursesMPWidget/coursesmpwidget.h Forms/CoursesMPWidget/coursesmpwidget.ui
    Forms/Download/download.cpp Forms/Download/download.h Forms/Download/download.ui
    Forms/GroupEditor/groupeditor.cpp Forms/GroupEditor/groupeditor.h Forms/GroupEditor/groupeditor.ui
    Forms/Loader/LoaderComponent/loadercomponent.cpp Forms/Loader/LoaderComponent/loadercomponent.h Forms/Loader/LoaderComponent/loadercomponent.ui
    Forms/Loader/loader.cpp Forms/Loader/loader.h Forms/Loader/loader.ui
    Forms/Main/mainwindow.cpp Forms/Main/mainwindow.h Forms/Main/mainwindow.ui
    Forms/MyWidget/mywidget.cpp Forms/MyWidget/mywidget.h Forms/MyWidget/mywidget.ui
    Forms/Notification/notification.cpp Forms/Notification/notification.h Forms/Notification/notification.ui
    Forms/PotokAdder/potokadder.cpp Forms/PotokAdder/potokadder.h Forms/PotokAdder/potokadder.ui
    Forms/Profile/profile.cpp Forms/Profile/profile.h Forms/Profile/profile.ui
    Forms/Reconnect/reconnect.cpp Forms/Reconnect/reconnect.h Forms/Reconnect/reconnect.ui
    Forms/Score/ScoreComponents/scorecomponents.cpp Forms/Score/ScoreComponents/scorecomponents.h Forms/Score/ScoreComponents/scorecomponents.ui
    Forms/Score/TestTaskComponents/testtaskcomponents.cpp Forms/Score/TestTaskComponents/testtaskcomponents.h Forms/Score/TestTaskComponents/testtaskcomponents.ui
    Forms/Score/score.cpp Forms/Score/score.h Forms/Score/score.ui
    StyleManager/stylemanager.cpp StyleManager/stylemanager.h
    XlsxUtils/xlsxutils.cpp XlsxUtils/xlsxutils.h
    main.cpp
    QXlsx/source/xlsxabstractooxmlfile.cpp QXlsx/header/xlsxabstractooxmlfile.h QXlsx/header/xlsxabstractooxmlfile_p.h
    QXlsx/source/xlsxabstractsheet.cpp QXlsx/header/xlsxabstractsheet.h QXlsx/header/xlsxabstractsheet_p.h
    QXlsx/source/xlsxcell.cpp QXlsx/header/xlsxcell.h QXlsx/header/xlsxcell_p.h
    QXlsx/source/xlsxcellformula.cpp QXlsx/header/xlsxcellformula.h QXlsx/header/xlsxcellformula_p.h
    QXlsx/source/xlsxcelllocation.cpp QXlsx/header/xlsxcelllocation.h
    QXlsx/source/xlsxcellrange.cpp QXlsx/header/xlsxcellrange.h
    QXlsx/source/xlsxcellreference.cpp QXlsx/header/xlsxcellreference.h
    QXlsx/source/xlsxchart.cpp QXlsx/header/xlsxchart.h QXlsx/header/xlsxchart_p.h
    QXlsx/source/xlsxchartsheet.cpp QXlsx/header/xlsxchartsheet.h QXlsx/header/xlsxchartsheet_p.h
    QXlsx/source/xlsxcolor.cpp QXlsx/header/xlsxcolor_p.h
    QXlsx/source/xlsxconditionalformatting.cpp QXlsx/header/xlsxconditionalformatting.h QXlsx/header/xlsxconditionalformatting_p.h
    QXlsx/source/xlsxcontenttypes.cpp QXlsx/header/xlsxcontenttypes_p.h
    QXlsx/source/xlsxdatavalidation.cpp QXlsx/header/xlsxdatavalidation.h QXlsx/header/xlsxdatavalidation_p.h
    QXlsx/source/xlsxdatetype.cpp QXlsx/header/xlsxdatetype.h
    QXlsx/source/xlsxdocpropsapp.cpp QXlsx/header/xlsxdocpropsapp_p.h
    QXlsx/source/xlsxdocpropscore.cpp QXlsx/header/xlsxdocpropscore_p.h
    QXlsx/source/xlsxdocument.cpp QXlsx/header/xlsxdocument.h QXlsx/header/xlsxdocument_p.h
    QXlsx/source/xlsxdrawing.cpp QXlsx/header/xlsxdrawing_p.h
    QXlsx/source/xlsxdrawinganchor.cpp QXlsx/header/xlsxdrawinganchor_p.h
    QXlsx/source/xlsxformat.cpp QXlsx/header/xlsxformat.h QXlsx/header/xlsxformat_p.h
    QXlsx/header/xlsxglobal.h
    QXlsx/source/xlsxmediafile.cpp QXlsx/header/xlsxmediafile_p.h
    QXlsx/source/xlsxnumformatparser.cpp QXlsx/header/xlsxnumformatparser_p.h
    QXlsx/source/xlsxrelationships.cpp QXlsx/header/xlsxrelationships_p.h
    QXlsx/source/xlsxrichstring.cpp QXlsx/header/xlsxrichstring.h QXlsx/header/xlsxrichstring_p.h
    QXlsx/source/xlsxsharedstrings.cpp QXlsx/header/xlsxsharedstrings_p.h
    QXlsx/source/xlsxsimpleooxmlfile.cpp QXlsx/header/xlsxsimpleooxmlfile_p.h
    QXlsx/source/xlsxstyles.cpp QXlsx/header/xlsxstyles_p.h
    QXlsx/source/xlsxtheme.cpp QXlsx/header/xlsxtheme_p.h
    QXlsx/source/xlsxutility.cpp QXlsx/header/xlsxutility_p.h
    QXlsx/source/xlsxworkbook.cpp QXlsx/header/xlsxworkbook.h QXlsx/header/xlsxworkbook_p.h
    QXlsx/source/xlsxworksheet.cpp QXlsx/header/xlsxworksheet.h QXlsx/header/xlsxworksheet_p.h
    QXlsx/source/xlsxzipreader.cpp QXlsx/header/xlsxzipreader_p.h
    QXlsx/source/xlsxzipwriter.cpp QXlsx/header/xlsxzipwriter_p.h
)
target_include_directories(LMS PRIVATE
    QXlsx
)

target_compile_definitions(LMS PRIVATE
    QT_DEPRECATED_WARNINGS
)

target_link_libraries(LMS PRIVATE
    Qt::Core
    Qt::Gui
    Qt::GuiPrivate
    Qt::Network
)


# Resources:
set(resourse_resource_files
    "resources/dowloadicon.png"
    "resources/dzicon3.png"
    "resources/exit.png"
    "resources/kap.jpg"
    "resources/profile.png"
    "resources/test.png"
)

qt_add_resources(LMS "resourse"
    PREFIX
        "/img"
    FILES
        ${resourse_resource_files}
)
set(resourse1_resource_files
    "resources/Comfortaa-Bold.ttf"
    "resources/Comfortaa-Regular.ttf"
)

qt_add_resources(LMS "resourse1"
    PREFIX
        "/font"
    FILES
        ${resourse1_resource_files}
)
set(resourse2_resource_files
    "ClientManager/certificate/client.key"
)

qt_add_resources(LMS "resourse2"
    PREFIX
        "/sll"
    FILES
        ${resourse2_resource_files}
)
set(resourse3_resource_files
    "resources/download.gif"
    "resources/reconnect.gif"
)

qt_add_resources(LMS "resourse3"
    PREFIX
        "/gif"
    FILES
        ${resourse3_resource_files}
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(LMS PRIVATE
        Qt::Widgets
    )
endif()

if(win32-g++)
    target_include_directories(LMS PRIVATE
        win32-gcc
    )
endif()

if(win32-msvc2013)
    target_include_directories(LMS PRIVATE
        msvc2013
    )
endif()

if(win32-msvc2015)
    target_include_directories(LMS PRIVATE
        msvc2015
    )
endif()

if(win32-msvc2017)
    target_include_directories(LMS PRIVATE
        msvc2017
    )
endif()

if(win32-msvc2019)
    target_include_directories(LMS PRIVATE
        msvc2019
    )
endif()

if(UNIX)
    target_include_directories(LMS PRIVATE
        unix-gcc
    )
endif()

if(APPLE)
    target_include_directories(LMS PRIVATE
        mac
    )
endif()

install(TARGETS LMS
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
