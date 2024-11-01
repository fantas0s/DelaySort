cmake_minimum_required(VERSION 3.5)

project(Test_DelaySort LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(delaysortUnitTest
    main.cpp
    tst_specialcases.h
    tst_specialcases.cpp
    tst_returnscorrectdelay_char.h
    tst_returnscorrectdelay_char.cpp
    tst_returnscorrectdelay_int.h
    tst_returnscorrectdelay_int.cpp
    receiverobject.h
    receiverobject.cpp
    DelaySort.h
    DelaySort.cpp
)
add_test(NAME specialcases COMMAND specialcases)
add_test(NAME returnsCorrectDelay_int COMMAND returnsCorrectDelay_int)
add_test(NAME returnscorrectdelay_char COMMAND returnscorrectdelay_char)

target_include_directories(delaysortUnitTest PUBLIC CMAKE_SOURCE_DIR)
target_link_libraries(delaysortUnitTest PRIVATE Qt${QT_VERSION_MAJOR}::Test)

