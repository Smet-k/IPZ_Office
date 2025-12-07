cmake_minimum_required(VERSION 3.16)

project(OfficeClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
    main.cpp
    homepage.h homepage.cpp
    mainwindow.h mainwindow.cpp
    statpage.cpp statpage.h
    newsletter.h
    stat.h
    loginmodal.h loginmodal.cpp
    logoutmodal.h logoutmodal.cpp
    newsletterpage.h newsletterpage.cpp
    clickablewidget.h
    managepage.h managepage.cpp
    employee.h
    editemployeepage.h editemployeepage.cpp
    editnewspage.h editnewspage.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OfficeClient
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        newsservice.h newsservice.cpp
        layouthelper.h layouthelper.cpp
        employeeservice.h employeeservice.cpp
        positionservice.h positionservice.cpp
        position.h
        statservice.h statservice.cpp

    )
    target_link_libraries(OfficeClient PRIVATE Qt6::Widgets Qt6::Network)
else()
    add_executable(OfficeClient ${PROJECT_SOURCES})
    target_link_libraries(OfficeClient PRIVATE Qt5::Widgets Qt5::Network)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OfficeClient)
endif()
