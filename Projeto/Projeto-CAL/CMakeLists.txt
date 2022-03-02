cmake_minimum_required(VERSION 3.17)
project(eStafetas)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

add_executable(eStafetas src/main.cpp
                         src/graph/Graph.cpp
                         src/entities/Package.cpp
                         src/entities/Vehicle.cpp
                         src/interface/Menu.cpp
                         src/graph/GraphElements.cpp
                         src/graph/GraphDataLoader.cpp src/interface/GraphDrawer.cpp src/interface/GraphDrawer.h)

target_link_libraries(eStafetas graphviewer)
