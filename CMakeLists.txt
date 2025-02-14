cmake_minimum_required(VERSION 3.3)
set(ProjectName VitalikLoh)
project(${ProjectName})

add_executable(${ProjectName}
	src/main.cpp
	
	src/resources/ResourceManager.h
	src/resources/ResourceManager.cpp
	src/resources/stb_image.h
	
	src/utils/Timer.h
	src/utils/Timer.cpp
	
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
	src/game/DynamicObjectsRenderer.h
	src/game/DynamicObjectsRenderer.cpp
	
	src/game/game_objects/GameObject.h
	src/game/game_objects/GameObject.cpp
	src/game/game_objects/Tank.h
	src/game/game_objects/Tank.cpp
	src/game/game_objects/BrickWall.h
	src/game/game_objects/BrickWall.cpp
	src/game/game_objects/BetonWall.h
	src/game/game_objects/BetonWall.cpp
	src/game/game_objects/Water.h
	src/game/game_objects/Water.cpp
	src/game/game_objects/Trees.h
	src/game/game_objects/Trees.cpp
	src/game/game_objects/Ice.h
	src/game/game_objects/Ice.cpp
	src/game/game_objects/Eagle.h
	src/game/game_objects/Eagle.cpp
	src/game/game_objects/Border.h
	src/game/game_objects/Border.cpp
	src/game/game_objects/Bullet.h
	src/game/game_objects/Bullet.cpp
	
	src/physics/PhysicsEngine.h
	src/physics/PhysicsEngine.cpp
	src/physics/collision/CollisionManager.h
	src/physics/collision/CollisionManager.cpp
	src/physics/collision/Collider.h
	src/physics/collision/Collider.cpp
	src/physics/collision/AABBCollider.h
	src/physics/collision/AABBCollider.cpp
	src/physics/collision/ICollidable.h
	src/physics/collision/ICollidable.cpp
	)

source_group("Header Files\\resources" FILES 
    src/resources/ResourceManager.h
    src/resources/stb_image.h
)

source_group("Header Files\\utils" FILES 
	src/utils/Timer.h
)

source_group("Header Files\\renderer" FILES 
    src/renderer/ShaderProgram.h
    src/renderer/Texture2D.h
    src/renderer/Sprite.h
    src/renderer/VertexBuffer.h
    src/renderer/IndexBuffer.h
    src/renderer/VertexArray.h
    src/renderer/VertexBufferLayout.h
    src/renderer/Renderer.h
    src/renderer/SpriteAnimator.h
)

source_group("Header Files\\game" FILES 
    src/game/Game.h
    src/game/Level.h
	src/game/DynamicObjectsRenderer.h
)

source_group("Header Files\\game\\game_objects" FILES 
    src/game/game_objects/GameObject.h
    src/game/game_objects/Tank.h
    src/game/game_objects/BrickWall.h
    src/game/game_objects/BetonWall.h
    src/game/game_objects/Water.h
    src/game/game_objects/Trees.h
    src/game/game_objects/Ice.h
    src/game/game_objects/Eagle.h
	src/game/game_objects/Border.h
	src/game/game_objects/Bullet.h
)

source_group("Header Files\\physics" FILES 
	src/physics/PhysicsEngine.h
)

source_group("Header Files\\physics\\collision" FILES 
	src/physics/collision/CollisionManager.h
	src/physics/collision/Collider.h
	src/physics/collision/AABBCollider.h
	src/physics/collision/ICollidable.h
)

source_group("Source Files\\resources" FILES 
    src/resources/ResourceManager.cpp
)

source_group("Source Files\\utils" FILES 
	src/utils/Timer.cpp
)

source_group("Source Files\\renderer" FILES 
    src/renderer/ShaderProgram.cpp
    src/renderer/Texture2D.cpp
    src/renderer/Sprite.cpp
    src/renderer/VertexBuffer.cpp
    src/renderer/IndexBuffer.cpp
    src/renderer/VertexArray.cpp
    src/renderer/VertexBufferLayout.cpp
    src/renderer/Renderer.cpp
    src/renderer/SpriteAnimator.cpp
)

source_group("Source Files\\game" FILES 
    src/game/Game.cpp
    src/game/Level.cpp
	src/game/DynamicObjectsRenderer.cpp
)

source_group("Source Files\\game\\game_objects" FILES 
    src/game/game_objects/GameObject.cpp
    src/game/game_objects/Tank.cpp
    src/game/game_objects/BrickWall.cpp
    src/game/game_objects/BetonWall.cpp
    src/game/game_objects/Water.cpp
    src/game/game_objects/Trees.cpp
    src/game/game_objects/Ice.cpp
    src/game/game_objects/Eagle.cpp
	src/game/game_objects/Border.cpp
	src/game/game_objects/Bullet.cpp
)

source_group("Source Files\\physics" FILES 
	src/physics/PhysicsEngine.cpp
)

source_group("Source Files\\physics\\collision" FILES 
	src/physics/collision/CollisionManager.cpp
	src/physics/collision/Collider.cpp
	src/physics/collision/AABBCollider.cpp
	src/physics/collision/ICollidable.cpp
)
target_compile_features(${ProjectName} PUBLIC cxx_std_17)

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

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ProjectName})