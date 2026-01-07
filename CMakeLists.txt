cmake_minimum_required(VERSION 4.2.0)

project(Renderer)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

add_executable(${PROJECT_NAME}
	./source/Source.cpp
	./source/include/Utility.cpp
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/source/include/
	C:/dep/boost_1_90_0
	C:/dep/glfw-3.4.bin.WIN32/include
	C:/dep/glew-2.3.0/include
)

target_link_libraries(${PROJECT_NAME}
	C:/dep/glfw-3.4.bin.WIN32/lib-vc2022/glfw3.lib
	C:/dep/glew-2.3.0/lib/Release/Win32/glew32s.lib
	opengl32.lib
)