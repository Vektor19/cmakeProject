cmake_minimum_required(VERSION 3.3)
set(ProjectName VitalikLoh)
project(${ProjectName})

add_executable(${ProjectName}
	src/main.cpp
	src/renderer/ShaderProgram.h
	src/renderer/ShaderProgram.cpp
	src/resources/ResourceManager.h
	src/resources/ResourceManager.cpp
	src/resources/stb_image.h
	src/renderer/Texture2D.h
	src/renderer/Texture2D.cpp
	src/renderer/Sprite.h
	src/renderer/Sprite.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${ProjectName} glfw)

add_subdirectory(external/glad)
target_link_libraries(${ProjectName} glad)

include_directories(external/glm)

set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${ProjectName} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${ProjectName}>/res)
