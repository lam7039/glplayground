cmake_minimum_required(VERSION 3.10)

project(glplayground)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(THIRD_PARTY_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/include")
set(THIRD_PARTY_SOURCE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/source")

include_directories(
    ${INCLUDE_DIR}
    ${THIRD_PARTY_INCLUDE_DIR}
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/source/*.cpp")

file(GLOB THIRD_PARTY_SOURCES
    "${THIRD_PARTY_SOURCE_DIR}/imgui/*.cpp"
    "${THIRD_PARTY_SOURCE_DIR}/glad/gl.c"
    "${THIRD_PARTY_SOURCE_DIR}/stbi/stbi_image.cpp"
)

list(APPEND SOURCES ${THIRD_PARTY_SOURCES})

add_executable(glplayground ${SOURCES})

target_link_libraries(glplayground PRIVATE glfw ${OPENGL_LIBRARIES})