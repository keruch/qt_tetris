cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(pl_project_1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME}
    main.cpp
    tetris.cpp
    tetris.h
    tetris.ui
    tetrisboard.cpp
    tetrisboard.h
    tetrispiece.cpp
    tetrispiece.h
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

find_package(Qt5 COMPONENTS Widgets Gamepad REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Gamepad)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    AUTOMOC ON
    AUTOUIC ON
    AURORCC ON
)

