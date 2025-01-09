cmake_minimum_required(VERSION 3.30)
project(SFMLTesting2)

set(CMAKE_CXX_STANDARD 17)

add_executable(SFMLTesting2 main.cpp
        Game.cpp
        Ball.cpp
)

target_link_libraries(SFMLTesting2 sfml-system sfml-window sfml-graphics)