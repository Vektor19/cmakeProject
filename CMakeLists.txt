cmake_minimum_required(VERSION 3.3)
set(ProjectName VitalikLoh)
project(${ProjectName})

add_executable(${ProjectName}
	src/main.cpp
	
	src/resources/ResourceManager.h
	src/resources/ResourceManager.cpp
	src/resources/stb_image.h
	
	src/renderer/ShaderProgram.h
	src/renderer/ShaderProgram.cpp
	src/renderer/Texture2D.h
	src/renderer/Texture2D.cpp
	src/renderer/Sprite.h
	src/renderer/Sprite.cpp
	src/renderer/VertexBuffer.h
	src/renderer/VertexBuffer.cpp
	src/renderer/IndexBuffer.h
	src/renderer/IndexBuffer.cpp
	src/renderer/VertexArray.h
	src/renderer/VertexArray.cpp
	src/renderer/VertexBufferLayout.h
	src/renderer/VertexBufferLayout.cpp
	src/renderer/Renderer.h
	src/renderer/Renderer.cpp
	src/renderer/SpriteAnimator.h
	src/renderer/SpriteAnimator.cpp
	
	src/game/Game.h
	src/game/Game.cpp
	src/game/Level.h
	src/game/Level.cpp
	src/game/game_objects/GameObject.h
	src/game/game_objects/GameObject.cpp
	src/game/game_objects/Tank.h
	src/game/game_objects/Tank.cpp
	src/game/game_objects/BrickWall.h
	src/game/game_objects/BrickWall.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${ProjectName} glfw)

add_subdirectory(external/glad)
target_link_libraries(${ProjectName} glad)

include_directories(external/glm)

include_directories(external/rapidjson/include)

set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${ProjectName} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${ProjectName}>/res)
