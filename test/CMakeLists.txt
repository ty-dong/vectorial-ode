cmake_minimum_required(VERSION 3.12)
project(ODE_Solver)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

set(Source_dir ../src)
set(Include_dir ../include)
set(Setting_dir ../Settings)
set(Sources  ${Source_dir}/ODE_System.cpp ${Source_dir}/ODE_solver.cpp ${Source_dir}/Input.cpp)
set(Headers ${Include_dir}/ODE_System.h ${Include_dir}/ODE_solver.h ${Include_dir}/Input.h ${Setting_dir}/User_defined_g.h)

add_subdirectory(googletest)

include_directories(googletest/include)
link_directories(googletest)

add_executable(test test.cpp ${Sources} ${Headers})
target_link_libraries(test gtest)
