cmake_minimum_required (VERSION 2.8)
project (Utils)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -l")

add_library(Utils STATIC src/Log.cpp src/clock.cpp include/Log.h include/NonCopyable.h include/clock.h)

include_directories(Utils include/)
# create the program
target_link_libraries(Utils ${CMAKE_DL_LIBS})
