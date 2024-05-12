cmake_minimum_required(VERSION 3.16)
project(server VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Concurrent Gui Network Sql Widgets)

qt_add_executable(server
    ../../common/authentication/authentication.cpp ../../common/authentication/authentication.h
    ../../common/authentication/group.cpp ../../common/authentication/group.h
    ../../common/course/course.cpp ../../common/course/course.h
    ../../common/course/course_components/coursecomponent.h
    ../../common/course/course_components/coursemediafiles.cpp ../../common/course/course_components/coursemediafiles.h
    ../../common/course/course_components/coursetask.cpp ../../common/course/course_components/coursetask.h
    ../../common/course/course_components/coursetest.cpp ../../common/course/course_components/coursetest.h
    ../../common/course/course_components/coursetutorials.cpp ../../common/course/course_components/coursetutorials.h
    ../../common/course/course_components/question.cpp ../../common/course/course_components/question.h
    ../../common/transferEnum/transferEnum.h
    database/databaseManager.cpp database/databaseManager.h
    database/queries.cpp
    jsonManager/jsonmanager.cpp jsonManager/jsonmanager.h
    main.cpp
    server/client.cpp server/client.h
    server/myserver.cpp server/myserver.h
    server/servertask.cpp server/servertask.h
)
target_link_libraries(server PRIVATE
    Qt::Concurrent
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Sql
    Qt::Widgets
)


# Resources:
set(resources_resource_files
    "server/certificate/server.crt"
    "server/certificate/server.key"
)

qt_add_resources(server "resources"
    PREFIX
        "/sll"
    FILES
        ${resources_resource_files}
)

if(MACOS)
    target_include_directories(server PRIVATE
        /Applications/Postgres.app/Contents/Versions/16/include
        /Applications/Postgres.app/Contents/Versions/16/lib
        /Users/valeriysofin/Qt/6.6.3/macos/plugins/sqldrivers
        /usr/local/mysql-connector-cpp/include
    )

    target_link_libraries(server PRIVATE
        # Remove: L/usr/local/lib
        pq
    )
endif()

install(TARGETS server
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
