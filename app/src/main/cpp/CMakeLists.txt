cmake_minimum_required(VERSION 3.22.1)

include_directories(libyuv/include)
add_subdirectory(libyuv)

# Declares and names the project.
project("yuvlib")

add_library( # Sets the name of the library.
        yuvlib
        SHARED
        native-lib.cpp)


find_library( # Sets the name of the path variable.
        log-lib
        log)


target_link_libraries( # Specifies the target library.
        yuvlib
        ${log-lib}
        yuv)