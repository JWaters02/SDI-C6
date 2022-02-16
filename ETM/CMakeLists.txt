cmake_minimum_required(VERSION 3.5)

project(ETM LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        mainform.cpp
        mainform.h
        mainform.ui
        Users/User.h
        Users/User.cpp
        Users/CargoOwner.h
        Users/CargoOwner.cpp
        Users/Drivers.h
        Users/Drivers.cpp
        Application/Login.cpp
        Application/Login.h
        Database/DBHandler.cpp
        Database/DBHandler.h
        Users/UserUtils.h
        Users/UserUtils.cpp
        Users/Forwarder.cpp
        Users/Forwarder.h
        Users/Courier.cpp
        Users/Courier.h
        Users/Consignee.cpp
        Users/Consignee.h
)

find_package(Qt5 COMPONENTS Widgets Mqtt REQUIRED)
find_package(Boost 1.70.0)

add_executable(ETM ${PROJECT_SOURCES})

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(ETM PRIVATE Qt5::Widgets Qt5::Mqtt -lpqxx -lpq -lbcrypt ${Boost_LIBRARIES})
