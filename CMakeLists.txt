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

add_executable(returnsCorrectDelay_int tst_returnscorrectdelay_int.cpp DelaySort.cpp DelaySort.h)
add_test(NAME returnsCorrectDelay_int COMMAND returnsCorrectDelay_int)

target_include_directories(returnsCorrectDelay_int PUBLIC CMAKE_SOURCE_DIR)
target_link_libraries(returnsCorrectDelay_int PRIVATE Qt${QT_VERSION_MAJOR}::Test)

