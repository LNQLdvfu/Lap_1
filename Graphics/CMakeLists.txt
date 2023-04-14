cmake_minimum_required(VERSION 3.23)
project(Graphics)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /opt/homebrew/Cellar/mesa)

add_executable(Graphics main.cpp)
add_definitions(-DGL_SILENCE_DEPRECATION)
#add_definitions(GL_SILENCE_DEPRECATION )
set( MESA_INCLUDE_DIRS /opt/homebrew/Cellar/mesa/22.3.6_1/include)
set( MESA_LIBRARY_DIRS /opt/homebrew/Cellar/mesa/22.3.6_1/lib)
# Thêm thư mục include của Mesa vào trong mã nguồn
include_directories(${MESA_INCLUDE_DIRS})

# Liên kết các thư viện của Mesa vào trong mã nguồn
target_link_libraries(Graphics ${MESA_LIBRARY_DIRS}/libOSMesa.dylib)


##openGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
add_definitions(${OPENGL_DEFINITIONS})
target_link_libraries(Graphics OpenGL)

# GLFW
find_package(glfw3 3.3.8 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARIES})
target_link_libraries(Graphics glfw)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
target_link_libraries(Graphics glew)

#glut
#find_package(glut REQUIRED)
#include_directories(${GLUT_INCLUDE_DIRS})
#link_libraries(${GLUT_LIBRARIES})
#target_link_libraries(Graphics glew)