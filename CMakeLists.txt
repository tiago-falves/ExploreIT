cmake_minimum_required(VERSION 3.15)
project(CAL1920)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "-pthread")

if (WIN32)
    link_libraries(ws2_32 wsock32)
endif (WIN32)


include_directories(src)
include_directories(src/Graph)
include_directories(src/Graph/GraphDrawer)
include_directories(src/Graph/GraphLoader)
include_directories(src/GraphViewer/cpp)
include_directories(src/Utils)

add_executable(CAL1920
        src/Graph/GraphDrawer/GraphDrawer.cpp
        src/Graph/GraphDrawer/GraphDrawer.h
        src/Graph/GraphLoader/GraphLoader.cpp
        src/Graph/GraphLoader/GraphLoader.h
        src/Graph/Edge.cpp
        src/Graph/Edge.h
        src/Graph/Graph.cpp
        src/Graph/Graph.h
        src/Graph/Node.cpp
        src/Graph/Node.h
        src/GraphViewer/cpp/connection.cpp
        src/GraphViewer/cpp/connection.h
        src/GraphViewer/cpp/edgetype.h
        src/GraphViewer/cpp/graphviewer.cpp
        src/GraphViewer/cpp/graphviewer.h
        src/Utils/MutablePriorityQueue.cpp
        src/Utils/MutablePriorityQueue.h
        src/Utils/Position.cpp
        src/Utils/Position.h
        src/Utils/utils.h
        src/main.cpp
        GraphViewerController.jar src/Graph/Preprocessor.cpp src/Graph/Preprocessor.h src/Menu/Menu.cpp src/Menu/Menu.h)

