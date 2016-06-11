cmake_minimum_required (VERSION 2.8)
project (GameApplication)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -l")

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(assimp REQUIRED)
find_package(TinyXML REQUIRED)

add_library(GameApplication STATIC src/GameApplication.cpp src/ProgramOptions.cpp src/CommandLineParser.cpp src/XMLOptionsParser.cpp src/utils/Log.cpp src/utils/time.cpp
include/Common.h include/GameApplication.h include/ProgramOptions.h include/ProgramOptions.h include/CommandLineParser.h include/XMLOptionsParser.h include/utils/Log.h
include/utils/NonCopyable.h include/utils/time.h)

include_directories(GameApplication include/ ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${assimp_INCLUDE_DIRS} ${TINYXML_INCLUDE_DIR})
# create the program
target_link_libraries(GameApplication ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${assimp_LIBRARIES} ${TINYXML_LIBRARIES} ${CMAKE_DL_LIBS})
