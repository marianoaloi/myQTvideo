cmake_minimum_required(VERSION 3.0.0)

project(myvideos VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_MODULE_PATH "/opt/qt5/5.15.2/gcc_64/include/**")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)
# find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED PATHS /opt/qt5/5.15.2/gcc_64/include/QtCore)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        component/mvideo.cpp
        component/mvideo.h
        component/mvideo.ui
        component/rangeslider.h
        component/rangeslider.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(myvideos
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET myvideos APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(myvideos SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(myvideos
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(myvideos PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(myvideos PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
target_link_libraries(myvideos PRIVATE Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
# target_include_directories(myvideos PRIVATE /opt/qt5/5.15.2/gcc_64/include/**)

set_target_properties(myvideos PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(myvideos)
endif()
