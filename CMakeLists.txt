cmake_minimum_required(VERSION 4.2.0)
set(CMAKE_CXX_STANDARD 17)

project(Renderer)

set(LIBS_DIR C:/dep)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

add_executable(${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/source/Source.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/source/vertex/VertexArray.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/vertex/VertexBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/vertex/IndexBuffer.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/source/shader/Shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/render/Renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/texture/Texture.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/source/include/Utility.cpp


	${LIBS_DIR}/imgui-1.92.5/imgui.cpp
	${LIBS_DIR}/imgui-1.92.5/imgui_demo.cpp
	${LIBS_DIR}/imgui-1.92.5/imgui_draw.cpp
	${LIBS_DIR}/imgui-1.92.5/imgui_tables.cpp
	${LIBS_DIR}/imgui-1.92.5/imgui_widgets.cpp
	${LIBS_DIR}/imgui-1.92.5/backends/imgui_impl_glfw.cpp
	${LIBS_DIR}/imgui-1.92.5/backends/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/source/include/
	${CMAKE_CURRENT_SOURCE_DIR}/source/vertex/
	${CMAKE_CURRENT_SOURCE_DIR}/source/shader/
	${CMAKE_CURRENT_SOURCE_DIR}/source/render/
	${CMAKE_CURRENT_SOURCE_DIR}/source/texture/


	${LIBS_DIR}/boost_1_90_0
	${LIBS_DIR}/glfw-3.4.bin.WIN32/include
	${LIBS_DIR}/glew-2.3.0/include
	${LIBS_DIR}/stb
	${LIBS_DIR}/glm-1.0.3
	${LIBS_DIR}/imgui-1.92.5
)

target_link_libraries(${PROJECT_NAME}
	${LIBS_DIR}/glfw-3.4.bin.WIN32/lib-vc2022/glfw3.lib
	${LIBS_DIR}/glew-2.3.0/lib/Release/Win32/glew32s.lib
	opengl32.lib
)