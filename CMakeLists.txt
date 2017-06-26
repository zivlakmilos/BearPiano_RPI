cmake_minimum_required(VERSION 2.8.11)
project(BearPiano)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

find_library(AUDIO_LIBRARY zaudio PATH /usr/local/lib/)

if(NOT AUDIO_LIBRARY)
    message(FATAL_ERROR "ERROR: Can't find zaudio audio library")
endif()

include_directories(
    include/
)

set(SOURCES
    src/bluetooth.cpp
)

set(LIBRARIES
    ${AUDIO_LIBRARY}
)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
