cmake_minimum_required(VERSION 3.21)
project(LAB3_2)
find_package(OpenMP)



add_executable(LAB3_2 main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(LAB3_2 PUBLIC OpenMP::OpenMP_CXX)
endif()