cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(SimulationClient LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

IF(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

find_package(OpenMP)

if (NOT OpenMP_CXX_FOUND)
  error("Cannot find OpenMP")
endif()

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
# Define executable
#
add_executable(Simulation_client ${CPP_SOURCES} ${C_SOURCES} ${CPP_HEADERS} ${IMGUI_SOURCES})

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
  imgui
)

#
# Copy shares dir
#
file(COPY Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
