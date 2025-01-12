cmake_minimum_required(VERSION 3.3)
set(ProjectName VitalikLoh)
project(${ProjectName})

add_executable(${ProjectName}
	src/main.cpp
	src/renderer/ShaderProgram.h
	src/renderer/ShaderProgram.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${ProjectName} glfw)

add_subdirectory(external/glad)
target_link_libraries(${ProjectName} glad)