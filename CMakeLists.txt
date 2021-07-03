cmake_minimum_required(VERSION 3.5)

project(SensorFusion LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_PREFIX_PATH "/Users/mohsen/Qt5.14.0/5.14.0/clang_64/lib/cmake/Qt5Test")
list(APPEND CMAKE_PREFIX_PATH "/Users/mohsen/Qt5.14.0/5.14.0/clang_64/lib/cmake/Qt5Network")
set(GTEST_USE_OWN_TR1_TUPLE=1)

add_definitions(-DRUN_TEST=1)
add_definitions(-DRUN_DEBUG=2)
add_definitions(-DRUN_APP=3)

# unset(TEST_ENABLE CACHE)
# unset(DEBUG_ENABLE CACHE)
# unset(APP_ENABLE CACHE)


option(TEST_ENABLE  ""  ON)
option(DEBUG_ENABLE ""  OFF)
option(APP_ENABLE   ""  OFF)

MESSAGE( STATUS ">> " TEST_ENABLE  " is " ${TEST_ENABLE} )
MESSAGE( STATUS ">> " DEBUG_ENABLE " is " ${DEBUG_ENABLE} )
MESSAGE( STATUS ">> " APP_ENABLE   " is " ${APP_ENABLE} )

if(APP_ENABLE)
    add_definitions(-DRUN_TYPE=RUN_APP)
    MESSAGE( STATUS ">> Configure Running App" )
elseif(TEST_ENABLE)
    add_definitions(-DRUN_TYPE=RUN_TEST)
    MESSAGE( STATUS ">> Configure Running Test" )
elseif(DEBUG_ENABLE)
    add_definitions(-DRUN_TYPE=RUN_DEBUG)
    MESSAGE( STATUS ">> Configure Running Debug" )
endif()

find_package(Qt5Test REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Core)
find_package(Qt5Network)
find_package(GTest CONFIG REQUIRED)


if(TEST_ENABLE)

    MESSAGE( STATUS ">> Add Executable for Test" )

    add_executable(SensorFusion

        ekf_localization.cpp
        run_localization.cpp
        input_parser.cpp
        tcp_server.cpp

        inc/ekf_localization.h
        inc/run_localization.h
        inc/input_parser.h
        inc/tcp_server.h

        tests/qtest_ekf_localization.cpp
        tests/qtest_run_localization.cpp
        tests/qtest_input_parser.cpp

        tests/inc/qtest_ekf_localization.h
        tests/inc/qtest_run_localization.h
        tests/inc/qtest_input_parser.h

        main.cpp
    )

else()

    MESSAGE( STATUS ">> Add Executable for Running App" )

    add_executable(SensorFusion

        ekf_localization.cpp
        run_localization.cpp
        input_parser.cpp
        tcp_server.cpp

        inc/ekf_localization.h
        inc/run_localization.h
        inc/input_parser.h
        inc/tcp_server.h

        main.cpp
    )

endif()


target_link_libraries(SensorFusion Qt5::Core Qt5::Network Eigen3::Eigen Qt5::Test GTest::gtest GTest::gmock)







