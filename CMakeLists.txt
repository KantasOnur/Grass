cmake_minimum_required(VERSION 3.28)
project(playground)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED) # Add this if GLFW is being used.

set(CMAKE_CXX_STANDARD 17)

# Add the ImGui include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include)

# Add ImGui implementation files
set(IMGUI_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/ImGui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/ImGui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/ImGui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/ImGui/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/ImGui/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/ImGui/imgui_impl_opengl3.cpp
        src/Core/Mesh/InstancedMesh.cpp
        src/Core/Mesh/InstancedMesh.h
        src/Core/Mesh/Tile.cpp
        src/Core/Mesh/Tile.h
)

add_executable(playground
        src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Core/Window.cpp
        src/Core/Window.h
        src/Core/Events/Events.h
        src/Core/Events/EventHandler.h
        src/Core/Events/EventHandler.cpp
        src/Scene.cpp
        src/Scene.h
        src/Core/OpenGL.h
        src/Core/Mesh/Mesh.cpp
        src/Core/Shader.cpp
        src/Core/Shader.cpp
        src/Core/Camera.cpp
        src/Core/Camera.h
        src/Game.cpp
        src/Core/Input/Input.h
        src/Core/Input/Input.cpp
        src/Core/Input/Input.h
        src/Core/Input/InputEvent.h
        src/Core/Gui.cpp
        src/Core/Gui.h
        ${IMGUI_SRC}  # Include ImGui source files
)

# Link GLFW and GLEW libraries
file(GLOB LIB_FILES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/*.dylib")
target_link_libraries(playground ${LIB_FILES} ${OPENGL_LIBRARIES} GLEW::GLEW glfw)

