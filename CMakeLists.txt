cmake_minimum_required(VERSION 3.16)

project(LibraryManagementGUI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic Qt tools
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(LibraryManagementGUI
    main.cpp
    lms_core.cpp
    loginwindow.cpp
    adminpanel.cpp
    customerpanel.cpp
    loginwindow.h
    adminpanel.h
    customerpanel.h
    lms_core.h


    loginwindow.ui
    adminpanel.ui
    customerpanel.ui
    addbookdialog.ui
    addbookdialog.h
    addbookdialog.cpp
    issuebookdialog.ui
    issuebookdialog.h
    issuebookdialog.cpp
    customer.h
    addcustomerdialog.ui
    addcustomerdialog.h
    addcustomerdialog.cpp
    customerlistdialog.ui
    customerlistdialog.cpp
    customerlistdialog.h




)

target_link_libraries(LibraryManagementGUI
    PRIVATE Qt6::Widgets
)
