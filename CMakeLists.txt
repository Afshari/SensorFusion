cmake_minimum_required(VERSION 3.5)

project(SensorFusion LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

MESSAGE( STATUS CMAKE_PREFIX_PATH " = " ${CMAKE_PREFIX_PATH} )

add_definitions(-DRUN_TEST=1)
add_definitions(-DRUN_DEBUG=2)
add_definitions(-DRUN_APP=3)

#unset(TEST_ENABLE  CACHE)
#unset(DEBUG_ENABLE CACHE)
#unset(APP_ENABLE   CACHE)

option(TEST_ENABLE  ""  OFF)
option(DEBUG_ENABLE ""  OFF)
option(APP_ENABLE   ""  ON)

MESSAGE( STATUS "-->> TEST_ENABLE  is " ${TEST_ENABLE}  )
MESSAGE( STATUS "-->> DEBUG_ENABLE is " ${DEBUG_ENABLE} )
MESSAGE( STATUS "-->> APP_ENABLE   is " ${APP_ENABLE}   )

if(APP_ENABLE)
    add_definitions(-DRUN_TYPE=RUN_APP)
    MESSAGE( STATUS "-->> Configure Running App" )
elseif(TEST_ENABLE)
    add_definitions(-DRUN_TYPE=RUN_TEST)
    MESSAGE( STATUS "-->> Configure Running Test" )
elseif(DEBUG_ENABLE)
    add_definitions(-DRUN_TYPE=RUN_DEBUG)
    MESSAGE( STATUS "-->> Configure Running Debug" )
endif()

find_package(Qt5Test REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Core)
find_package(Qt5Network)
find_package(GTest CONFIG REQUIRED)

set(SOURCES ekf_localization.cpp        ################## SOURCE FILES ##################
    run_localization.cpp
    kf_tracking.cpp
    run_tracking.cpp
    kf_passive_suspension.cpp
    run_suspension_estimator.cpp
    input_parser.cpp
    tcp_server.cpp
    inc/ekf_localization.h              ################## HEADER FILES ##################
    inc/run_localization.h
    inc/kf_tracking.h
    inc/run_tracking.h
    inc/kf_passive_suspension.h
    inc/run_suspension_estimator.h
    inc/input_parser.h
    inc/tcp_server.h
    main.cpp                            ################## MAIN FILE ##################
 )


if(TEST_ENABLE)

    MESSAGE( STATUS "-->> Add Executable for Test" )

    set(SOURCES ${SOURCES}
            tests/qtest_ekf_localization.cpp
            tests/qtest_run_localization.cpp
            tests/qtest_kf_tracking.cpp
            tests/qtest_kf_passive_suspension.cpp
            tests/qtest_run_suspension_estimator.cpp
            tests/qtest_input_parser.cpp
            tests/inc/qtest_ekf_localization.h
            tests/inc/qtest_run_localization.h
            tests/inc/qtest_kf_tracking.h
            tests/inc/qtest_kf_passive_suspension.h
            tests/inc/qtest_run_suspension_estimator.h
            tests/inc/qtest_input_parser.h
        )

else()

    MESSAGE( STATUS "-->> Add Executable for Running App" )

endif()

MESSAGE( STATUS "-->> Source Files for Compilation: " ${SOURCES} )


add_executable(SensorFusion
    ${SOURCES} )


if(TEST_ENABLE)

target_link_libraries(SensorFusion Qt5::Core Qt5::Network Eigen3::Eigen Qt5::Test GTest::gtest GTest::gmock)

else()

target_link_libraries(SensorFusion Qt5::Core Qt5::Network Eigen3::Eigen)

endif()






