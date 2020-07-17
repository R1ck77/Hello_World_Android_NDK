# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)

add_library(lua SHARED IMPORTED)

set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/")
string(APPEND PATH ${ANDROID_ABI})
string(APPEND PATH "/liblua.so")
message(STATUS "DEBUG: x=${PATH}")

set_property(TARGET lua PROPERTY IMPORTED_LOCATION "${PATH}")


add_library(native-lib SHARED native-lib.cpp )

include_directories("include")

target_include_directories(native-lib PUBLIC lua)
           
find_library(log-lib log)

target_link_libraries(native-lib
                       ${log-lib}
                       lua)
