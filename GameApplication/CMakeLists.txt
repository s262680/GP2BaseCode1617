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

add_library(GameApplication STATIC src/Graphics.cpp src/Shader.cpp src/Texture.cpp src/FBXLoader.cpp src/FileSystem.cpp src/GameApplication.cpp src/GameObject.cpp
  src/Timer.cpp src/Components/Material.cpp src/Components/Transform.cpp src/Components/Mesh.cpp src/Components/Camera.cpp src/IMGUI/imgui_demo.cpp src/IMGUI/imgui_draw.cpp src/IMGUI/imgui.cpp
  src/IMGUI/imgui_impl_sdl_gl3.cpp src/Resource/Resource.cpp
include/Common.h include/FBXLoader.h include/Graphics.h include/Shader.h include/Vertices.h include/Texture.h include/MeshData.h include/FileSystem.h include/GameApplication.h include/GameObject.h include/Timer.h
include/Components/Component.h include/Components/Material.h include/Components/Transform.h include/Components/Mesh.h include/Components/Components.h include/Components/Camera.h include/Resource/Resource.h
include/IMGUI/imconfig.h include/IMGUI/imgui_internal.h include/IMGUI/imgui.h include/IMGUI/stb_rect_pack.h include/IMGUI/stb_textedit.h include/IMGUI/stb_truetype.h include/IMGUI/imgui_impl_sdl_gl3.h)

include_directories(GameApplication include/ ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${assimp_INCLUDE_DIRS})
# create the program
target_link_libraries(GameApplication ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${assimp_LIBRARIES} ${CMAKE_DL_LIBS})
