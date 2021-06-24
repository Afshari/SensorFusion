cmake_minimum_required(VERSION 3.5)

project(SensorFusion LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)


find_package(Qt5Test REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Core)
find_package(Qt5Network)


add_executable(SensorFusion
    main.cpp
)
target_link_libraries(SensorFusion Qt5::Core Qt5::Test Qt5::Network Eigen3::Eigen)
