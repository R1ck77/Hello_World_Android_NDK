# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)

add_library(native-lib SHARED native-lib.cpp )

add_subdirectory(lua)

target_include_directories(native-lib PUBLIC lua)
           
find_library(log-lib log)

target_link_libraries(native-lib
                       ${log-lib}
                       lua)
