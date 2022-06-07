cmake_minimum_required(VERSION 3.10)
project(Visualizer)

if(WIN320){
    set(SFML_INCLUDE_DIR    lib/MinGW/SFML-2.5.1/include)
    set(SFML_LIBRARY_DIR    lib/MinGW/SFML-2.5.1/lib)
    set(SFML_DIR            lib/MinGW/SFML-2.5.1/lib/cmake/SFML)
} else {
    set(SFML_INCLUDE_DIR    lib/GCC/SFML-2.5.1/include)
    set(SFML_LIBRARY_DIR    lib/GCC/SFML-2.5.1/lib)
    set(SFML_DIR            lib/GCC/SFML-2.5.1/lib/cmake/SFML)
}

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(Visualizer src/main.cpp src/visualizer.cpp src/visualizer.hpp)
target_link_libraries (Visualizer sfml-graphics sfml-window sfml-system)