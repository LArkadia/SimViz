cmake_minimum_required(VERSION 3.25)
project(SimViz)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

#GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

#GLFW
find_package(glfw3 3.3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#GLM
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})




add_executable(SimViz
        src/main.cpp
        lib/Sim_Viz/Sim_viz.hpp
        lib/Sim_Viz/Sim_viz.cpp
)
target_link_libraries(SimViz ${GLEW_LIBRARIES} glfw OpenGL::GL ${GLM_LIBRARIES})
