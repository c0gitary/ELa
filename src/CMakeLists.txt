file(GLOB_RECURSE SRC_FILE "*.cpp")
set(SRC ${SRC_FILE})

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/include)

