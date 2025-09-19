cmake_minimum_required(VERSION 3.16)
project(Swipe)

add_executable(Swipe src/main.cpp src/block.cpp src/dividedentity.cpp src/gap.cpp src/loop.cpp src/renderwindow.cpp src/utils.cpp
src/collider.cpp src/entity.cpp src/general.cpp src/main.cpp src/resizable.cpp src/variable.cpp
src/compiler.cpp src/funchead.cpp src/heightchanger.cpp src/math.cpp src/textbox.cpp)

add_subdirectory(external/SDL-release-2.32.10)
add_subdirectory(external/SDL_image-release-2.8.6) 
add_subdirectory(external/SDL_ttf-release-2.24.0) 

target_link_libraries(Swipe SDL2 SDL2_image SDL2_ttf)

if (WIN32)
    target_link_libraries(
        Swipe SDL2main
    )
endif()

add_custom_command(
    TARGET Swipe POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL2>"
        "$<TARGET_FILE:SDL2_image>" 
        "$<TARGET_FILE:SDL2_ttf>" 
        "$<TARGET_FILE_DIR:Swipe>"
    VERBATIM
)
target_include_directories(
    Swipe PRIVATE external/SDL-release-2.32.10/include include
)