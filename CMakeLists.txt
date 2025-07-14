cmake_minimum_required(VERSION 3.20.0)

project(PTAHomework VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# tempcxx 
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(temp temp.cpp)
target_link_libraries(temp ${OpenCV_LIBRARIES})

#message(STATUS "OpenCV version: ${OpenCV_VERSION}")
#message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
#message(STATUS "OpenCV libraries: ${OpenCV_LIBRARIES}")

# tempc
add_executable(ctemp temp.c)

# PID
add_executable(PID tech-try/PID/PID.cpp)
target_include_directories(PID PRIVATE tech-try/PID)

# Perspective
add_executable(Perspective tech-try/Perspective.cpp)
add_executable(StateMachine tech-try/StateMachine/StateMachine.cpp tech-try/StateMachine/StateMachine.hpp)
target_link_libraries(Perspective ${OpenCV_LIBRARIES})

add_subdirectory(tech-try/Http)
