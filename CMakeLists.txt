cmake_minimum_required(VERSION 3.5)

project(CinderCellEditor LANGUAGES CXX)

set(VERSION 0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    CinderCellEditor.cpp
    Item.cpp
    CinderMap.cpp
    Controls.cpp
    switch.cpp
    Cursor.cpp
    Overlay.cpp
    )


set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/bin/sfml/include")
set(SFML_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/bin/sfml/lib")

link_directories(${SFML_LIBRARY_DIR})
include_directories(${SFML_INCLUDE_DIR})

add_executable(cce ${SOURCES})

target_link_libraries (cce sfml-graphics sfml-window sfml-system)

add_compile_definitions(VERSION="${VERSION}")

# Resources
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})