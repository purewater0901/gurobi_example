cmake_minimum_required(VERSION 3.14)
project(socp)

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11 -g -D_GLIBCXX_USE_CXX11_ABI=0")
    set(GUROBI_INCLUDE_DIRECTORY "/Library/gurobi811/mac64/include")
    set(GUROBI_LIB_DIRECTORY "/Library/gurobi811/mac64/lib")
    set(SOURCE_FILES src/main.cpp ${GUROBI_INCLUDE_DIRECTORY}/gurobi_c++.h)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11 -g -D_GLIBCXX_USE_CXX11_ABI=0")
    set(GUROBI_INCLUDE_DIRECTORY "/opt/gurobi811/linux64/include")
    set(GUROBI_LIB_DIRECTORY "/opt/gurobi811/linux64/lib")
    set(SOURCE_FILES main.cpp ${GUROBI_INCLUDE_DIRECTORY}/gurobi_c++.h)
endif()

include_directories(${GUROBI_INCLUDE_DIRECTORY})
link_directories(${GUROBI_LIB_DIRECTORY})

include_directories(include)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(socp_prc main.cpp)
target_link_libraries (socp_prc gurobi_c++)
target_link_libraries (socp_prc gurobi81)

add_executable(socp_prc2 example2.cpp)
target_link_libraries (socp_prc2 gurobi_c++)
target_link_libraries (socp_prc2 gurobi81)
