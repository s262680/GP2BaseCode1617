cmake_minimum_required (VERSION 2.8)
project (OpenGLRenderer)

set(CMAKE_PREFIX_PATH "C:/Dev/glew/include")
set(CMAKE_LIBRARY_PATH "C:/Dev/glew/lib/Release/x64")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -l")

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

add_library(OpenGLRenderer STATIC src/OpenGLRenderer.cpp include/OpenGLRenderer.h)

include_directories(OpenGLRenderer include/ ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
# create the program
target_link_libraries(OpenGLRenderer ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${CMAKE_DL_LIBS})
