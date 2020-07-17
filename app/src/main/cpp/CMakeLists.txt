# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)

add_library(native-lib SHARED native-lib.cpp)
include_directories("include/guile/2.2" "include")

add_library(guile-2.2 SHARED IMPORTED)
set_property(TARGET guile-2.2 PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI}/libguile-2.2.so)
target_include_directories(native-lib PUBLIC guile-2.2)

add_library(gc SHARED IMPORTED)
set_property(TARGET gc PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI}/libgc.so)
target_include_directories(native-lib PUBLIC gc)

add_library(ffi SHARED IMPORTED)
set_property(TARGET ffi PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI}/libffi.so)
target_include_directories(native-lib PUBLIC ffi)

add_library(unistring SHARED IMPORTED)
set_property(TARGET unistring PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI}/libunistring.so)
target_include_directories(native-lib PUBLIC unistring)

add_library(iconv SHARED IMPORTED)
set_property(TARGET iconv PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI}/libiconv.so)
target_include_directories(native-lib PUBLIC iconv)

add_library(gmp SHARED IMPORTED)
set_property(TARGET gmp PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI}/libgmp.so)
target_include_directories(native-lib PUBLIC gmp)

add_library(ltdl SHARED IMPORTED)
set_property(TARGET ltdl PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI}/libltdl.so)
target_include_directories(native-lib PUBLIC ltdl)



find_library(log-lib log)

target_link_libraries(native-lib ${log-lib} guile-2.2 gc ffi unistring iconv gmp ltdl)
