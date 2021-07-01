cmake_minimum_required(VERSION 3.5)

project(SensorFusion LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_definitions(-DRUN_TEST=1)
add_definitions(-DRUN_DEBUG=2)
add_definitions(-DRUN_APP=3)

add_definitions(-DRUN_TYPE=RUN_TEST)

find_package(Qt5Test REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Core)
find_package(Qt5Network)
find_package(GTest CONFIG REQUIRED)


add_executable(SensorFusion

    ekf_localization.cpp
    run_localization.cpp
    inc/ekf_localization.h
    inc/run_localization.h

    tests/qtest_ekf_localization.cpp
    tests/qtest_run_localization.cpp
    tests/inc/qtest_ekf_localization.h
    tests/inc/qtest_run_localization.h

    main.cpp
)



target_link_libraries(SensorFusion Qt5::Core Qt5::Network Eigen3::Eigen Qt5::Test GTest::gtest)







