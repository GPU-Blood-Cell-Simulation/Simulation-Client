cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(SimulationClient LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

IF(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

find_package(OpenMP REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(gstreamer REQUIRED IMPORTED_TARGET gstreamer-1.0>=1.4)
pkg_search_module(gstreamer-app REQUIRED IMPORTED_TARGET gstreamer-app-1.0>=1.4)

#
# Program sources
#
file(GLOB_RECURSE C_SOURCES "src/*.c")
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE CPP_HEADERS "src/*.hpp" "src/*.h")
file(GLOB_RECURSE IMGUI_SOURCES "Libraries/include/imgui/*.cpp")

#
# Add imgui library
#
add_library(imgui ${IMGUI_SOURCES})

#
# Add imgui file dialog library
#
add_subdirectory("Libraries/include/imgui_file_dialog")
target_link_libraries(ImGuiFileDialog PUBLIC imgui)
target_include_directories(ImGuiFileDialog PUBLIC ${CMAKE_SOURCE_DIR}/Libraries/include/)

#
# Add imgui stdlib
#
add_library(ImGuiStdLib
  ${CMAKE_SOURCE_DIR}/Libraries/include/imgui_stdlib/imgui_stdlib.cpp
  ${CMAKE_SOURCE_DIR}/Libraries/include/imgui_stdlib/imgui_stdlib.h
)
target_link_libraries(ImGuiStdLib PUBLIC imgui)
target_include_directories(ImGuiStdLib PUBLIC ${CMAKE_SOURCE_DIR}/Libraries/include/)

#
# Define executable
#
add_executable(Simulation_client ${CPP_SOURCES} ${C_SOURCES} ${CPP_HEADERS})

#
# Add header files
#
include_directories(${CMAKE_SOURCE_DIR}/Libraries/include/)

#
# Add libraries
#
target_link_libraries(Simulation_client PUBLIC
  OpenMP::OpenMP_CXX
  ${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a
  ${CMAKE_SOURCE_DIR}/Libraries/lib/libenet.a
  imgui
  ImGuiStdLib
  ImGuiFileDialog
  PkgConfig::gstreamer
  PkgConfig::gstreamer-app
)

#
# Copy shares dir
#
file(COPY Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#
# Tests
#


list(REMOVE_ITEM CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_library(test_client ${CPP_SOURCES} ${C_SOURCES} ${CPP_HEADERS})
target_link_libraries(test_client PUBLIC
  OpenMP::OpenMP_CXX
  ${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a
  ${CMAKE_SOURCE_DIR}/Libraries/lib/libenet.a
  imgui
  ImGuiFileDialog
  PkgConfig::gstreamer
  PkgConfig::gstreamer-app
)

#add_subdirectory("src/")
include(CTest)
add_subdirectory("${PROJECT_SOURCE_DIR}/Libraries/googletest-1.14.0/")
add_subdirectory("tests/")
