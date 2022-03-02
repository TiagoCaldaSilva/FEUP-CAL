cmake_minimum_required(VERSION 3.17)
project(CAL-TP_classes)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

file(GLOB TP8_GRAPHVIEWER_FILES CONFIGURE_DEPENDS
        "TP8_graphviewer/*.cpp"
        )

add_executable(TP8_graphviewer
        ${TP8_GRAPHVIEWER_FILES}
        )

target_link_libraries(TP8_graphviewer graphviewer)
