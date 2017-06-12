cmake_minimum_required(VERSION 2.8.11)
project(BearPiano)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

include_directories(
    include/
)

set(SOURCES
    src/sdl/audioplayersdl.cpp
)

set(LIBRARIES
    ${SDL2_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
