cmake_minimum_required(VERSION 3.16)
project(QXlsx VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)

qt_add_library(QXlsx
    xlsxabstractooxmlfile.cpp xlsxabstractooxmlfile.h xlsxabstractooxmlfile_p.h
    xlsxabstractsheet.cpp xlsxabstractsheet.h xlsxabstractsheet_p.h
    xlsxcell.cpp xlsxcell.h xlsxcell_p.h
    xlsxcellformula.cpp xlsxcellformula.h xlsxcellformula_p.h
    xlsxcelllocation.cpp xlsxcelllocation.h
    xlsxcellrange.cpp xlsxcellrange.h
    xlsxcellreference.cpp xlsxcellreference.h
    xlsxchart.cpp xlsxchart.h xlsxchart_p.h
    xlsxchartsheet.cpp xlsxchartsheet.h xlsxchartsheet_p.h
    xlsxcolor.cpp xlsxcolor_p.h
    xlsxconditionalformatting.cpp xlsxconditionalformatting.h xlsxconditionalformatting_p.h
    xlsxcontenttypes.cpp xlsxcontenttypes_p.h
    xlsxdatavalidation.cpp xlsxdatavalidation.h xlsxdatavalidation_p.h
    xlsxdatetype.cpp xlsxdatetype.h
    xlsxdocpropsapp.cpp xlsxdocpropsapp_p.h
    xlsxdocpropscore.cpp xlsxdocpropscore_p.h
    xlsxdocument.cpp xlsxdocument.h xlsxdocument_p.h
    xlsxdrawing.cpp xlsxdrawing_p.h
    xlsxdrawinganchor.cpp xlsxdrawinganchor_p.h
    xlsxformat.cpp xlsxformat.h xlsxformat_p.h
    xlsxglobal.h
    xlsxmediafile.cpp xlsxmediafile_p.h
    xlsxnumformatparser.cpp xlsxnumformatparser_p.h
    xlsxrelationships.cpp xlsxrelationships_p.h
    xlsxrichstring.cpp xlsxrichstring.h xlsxrichstring_p.h
    xlsxsharedstrings.cpp xlsxsharedstrings_p.h
    xlsxsimpleooxmlfile.cpp xlsxsimpleooxmlfile_p.h
    xlsxstyles.cpp xlsxstyles_p.h
    xlsxtheme.cpp xlsxtheme_p.h
    xlsxutility.cpp xlsxutility_p.h
    xlsxworkbook.cpp xlsxworkbook.h xlsxworkbook_p.h
    xlsxworksheet.cpp xlsxworksheet.h xlsxworksheet_p.h
    xlsxzipreader.cpp xlsxzipreader_p.h
    xlsxzipwriter.cpp xlsxzipwriter_p.h
)
target_include_directories(QXlsx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(QXlsx PUBLIC
    QT_DEPRECATED_WARNINGS QT_DEPRECATED_WARNINGS
)

target_link_libraries(QXlsx PUBLIC
    Qt::Core
    Qt::Gui
    Qt::GuiPrivate
)

if(win32-g++)
    target_include_directories(QXlsx PUBLIC
        win32-gcc
    )
endif()

if(win32-msvc2013)
    target_include_directories(QXlsx PUBLIC
        msvc2013
    )
endif()

if(win32-msvc2015)
    target_include_directories(QXlsx PUBLIC
        msvc2015
    )
endif()

if(win32-msvc2017)
    target_include_directories(QXlsx PUBLIC
        msvc2017
    )
endif()

if(win32-msvc2019)
    target_include_directories(QXlsx PUBLIC
        msvc2019
    )
endif()

if(UNIX)
    target_include_directories(QXlsx PUBLIC
        unix-gcc
    )
endif()

if(APPLE)
    target_include_directories(QXlsx PUBLIC
        mac
    )
endif()

install(TARGETS QXlsx
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
