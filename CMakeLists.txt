cmake_minimum_required(VERSION 3.16)
project(Swipe)

add_executable(Swipe src/main.cpp src/block.cpp src/dividedentity.cpp src/gap.cpp src/loop.cpp src/renderwindow.cpp src/utils.cpp
src/collider.cpp src/entity.cpp src/general.cpp src/main.cpp src/resizable.cpp src/variable.cpp
src/compiler.cpp src/funchead.cpp src/heightchanger.cpp src/math.cpp src/textbox.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

target_include_directories(Swipe PUBLIC include)

target_link_libraries(Swipe ${SDL2_MIXER_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})