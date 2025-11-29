cmake_minimum_required( VERSION 3.16 )
project ( AII LANGUAGES CXX
            VERSION 0.0.1)

set(CMAKE_AUTOMOC on)

find_package( Qt6 REQUIRED Widgets Gui Core )
add_executable( aii src/main.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h)

target_link_libraries( aii Qt6::Widgets Qt6::Gui Qt6::Core )