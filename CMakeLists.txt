cmake_minimum_required(VERSION 3.25)
project(kowboj)

set(CMAKE_CXX_STANDARD 17)

add_executable(kowboj main.cpp)
target_link_libraries( kowboj -lmingw32 -lallegro-5.0.10-monolith-mt-debug)