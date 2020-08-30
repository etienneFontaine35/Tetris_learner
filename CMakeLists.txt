cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(Tetris_learner)
set(CMAKE_CXX_STANDARD 14)

set(SOURCES_LIST "game_manager.cpp" "graphics.cpp" "grid.cpp" "main.cpp" "player.cpp" "tetris_ai.cpp")
set(EXECUTABLE_NAME "Tetris_learner")


add_executable(Tetris_learner ${SOURCES_LIST})
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_range_for)

# location of PyTorch C++ API
set(TORCH_INSTALL_DIR "/usr/local/libtorch")
set(Torch_DIR "${TORCH_INSTALL_DIR}/share/cmake/Torch")
find_package(Torch REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} ${TORCH_LIBRARIES})

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics)