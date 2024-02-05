cmake_minimum_required(VERSION 3.27)
project(tic_tac_toe_game)


add_library(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/computer_turn.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game_checkers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interactive_messages.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/non_interactive_messages.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/normal_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/unfair_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/user_turn.c)

# target_include_directories(HEADER_FILES
#     ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${SOURCE_FILES})


add_subdirectory(include)
add_subdirectory(src)