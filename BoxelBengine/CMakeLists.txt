cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

project(bengine VERSION 0.1)

file(GLOB_RECURSE SRC_FILES 
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.c 
  ${CMAKE_SOURCE_DIR}/external/imgui/imgui.cpp
  ${CMAKE_SOURCE_DIR}/external/imgui/imgui_draw.cpp
  ${CMAKE_SOURCE_DIR}/external/imgui/imgui_tables.cpp
  ${CMAKE_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
  ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
  ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
)

file(GLOB_RECURSE H_FILES 
  ${CMAKE_SOURCE_DIR}/src/*.hpp 
  ${CMAKE_SOURCE_DIR}/src/*.h
  ${CMAKE_SOURCE_DIR}/external.imgui/*.hpp
  ${CMAKE_SOURCE_DIR}/external.imgui/*.h
)


add_executable(${PROJECT_NAME} ${H_FILES} ${SRC_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(OpenGL_GL_PREFERENCE GLVND)

#find and build dependencies
find_package(OpenGL REQUIRED)
add_definitions(-DGLEW_STATIC)
add_subdirectory(external/glfw EXCLUDE_FROM_ALL)
add_subdirectory(external/glew EXCLUDE_FROM_ALL)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)

add_library(STB_IMAGE "external/stb_image/stb_image.cpp") 
add_library(IMGUI "external/imgui/imgui.cpp")

set(LIBS glfw OpenGL::GL ${CMAKE_DL_LIBS} libglew_static STB_IMAGE IMGUI glm)

include_directories(
  "${CMAKE_SOURCE_DIR}/src"
  "${CMAKE_SOURCE_DIR}/src/primitives/"
  "${CMAKE_SOURCE_DIR}/src/scenes/"
  "${CMAKE_SOURCE_DIR}/external/imgui/backends/"
  "${CMAKE_SOURCE_DIR}/external/imgui/"
  "${CMAKE_SOURCE_DIR}/external/"
)

target_link_libraries(${PROJECT_NAME} ${LIBS})

#copy resources to build directory
file(COPY "${CMAKE_SOURCE_DIR}/res/" DESTINATION "${CMAKE_BINARY_DIR}/res/")

