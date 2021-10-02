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

set( SET_RUN_TEST   "1")
set( SET_RUN_DEBUG  "2")
set( SET_RUN_APP    "3")

##### Here you can define the Running Mode of the Application #####
set( SET_RUN_TYPE ${SET_RUN_APP} )


find_package(Qt5Test REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Core)
find_package(Qt5Network)


set(SOURCES src/ekf_localization.cpp        ################## SOURCE FILES ##################
    src/pf_localization.cpp
    src/pf_object.cpp
    src/pf_robot.cpp
    src/pf_particle.cpp
    src/run_localization.cpp
    src/kf_tracking.cpp
    src/run_tracking.cpp
    src/kf_passive_suspension.cpp
    src/run_suspension_estimator.cpp
    src/input_parser.cpp
    inc/ekf_localization.h                  ################## HEADER FILES ##################
    inc/pf_localization.h
    inc/pf_object.h
    inc/pf_robot.h
    inc/pf_particle.h
    inc/run_localization.h
    inc/kf_tracking.h
    inc/run_tracking.h
    inc/kf_passive_suspension.h
    inc/run_suspension_estimator.h
    inc/input_parser.h
    main.cpp                                ################## MAIN FILE ##################
 )

include_directories(inc/stats)

if( ${SET_RUN_TYPE} MATCHES ${SET_RUN_TEST} )

    MESSAGE( STATUS "-->> Add Executable for Test" )
    add_definitions(-DRUN_TYPE=RUN_TEST)
    find_package(GTest CONFIG REQUIRED)

    set(SOURCES ${SOURCES}
            tests/qtest_ekf_localization.cpp
            tests/qtest_pf_object.cpp
            tests/qtest_pf_particle.cpp
            tests/qtest_run_localization.cpp
            tests/qtest_kf_tracking.cpp
            tests/qtest_kf_passive_suspension.cpp
            tests/qtest_run_suspension_estimator.cpp
            tests/qtest_input_parser.cpp
            tests/inc/qtest_ekf_localization.h
            tests/inc/qtest_pf_object.h
            tests/inc/qtest_pf_particle.h
            tests/inc/qtest_run_localization.h
            tests/inc/qtest_kf_tracking.h
            tests/inc/qtest_kf_passive_suspension.h
            tests/inc/qtest_run_suspension_estimator.h
            tests/inc/qtest_input_parser.h
        )

    add_executable(TestSensorFusion
        ${SOURCES} )

    target_link_libraries(TestSensorFusion Qt5::Core Qt5::Network Eigen3::Eigen Qt5::Test GTest::gtest GTest::gmock)

elseif( ${SET_RUN_TYPE} MATCHES ${SET_RUN_DEBUG} )

    MESSAGE( STATUS "-->> Add Executable for Debug" )
    add_definitions(-DRUN_TYPE=RUN_DEBUG)
    set(SOURCES ${SOURCES}
        src/debug_server.cpp
        inc/debug_server.h
    )

    add_executable(DebugSensorFusion
        ${SOURCES} )

    target_link_libraries(DebugSensorFusion Qt5::Core Qt5::Network Eigen3::Eigen)

elseif( ${SET_RUN_TYPE} MATCHES ${SET_RUN_APP} )

    MESSAGE( STATUS "-->> Add Executable for Running App" )
    add_definitions(-DRUN_TYPE=RUN_APP)
    add_executable(SensorFusion
        src/tcp_server.cpp
        inc/tcp_server.h
        ${SOURCES} )
    target_link_libraries(SensorFusion Qt5::Core Qt5::Network Eigen3::Eigen)

endif()

#MESSAGE( STATUS "-->> Source Files for Compilation: " ${SOURCES} )







