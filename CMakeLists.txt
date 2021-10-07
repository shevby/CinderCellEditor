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
    )

set(HEADERS
    constants.h
    CinderCellEditor.h
    Item.h
    CinderMap.h
    Controls.h
    switch.h
    )

set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/bin/sfml/include")
set(SFML_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/bin/sfml/lib")

link_directories(${SFML_LIBRARY_DIR})
include_directories(${SFML_INCLUDE_DIR})

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(cce ${SOURCES} ${HEADERS})

target_link_libraries (cce sfml-graphics sfml-window sfml-system)

add_compile_definitions(VERSION="${VERSION}")
