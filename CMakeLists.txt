cmake_minimum_required(VERSION 3.1)
project(ODE_Solver)
set(CMAKE_CXX_STANDARD 14)

set(Source_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(Setting_dir ${CMAKE_CURRENT_SOURCE_DIR}/settings)

set(Sources ${Source_dir}/main.cpp ${Source_dir}/ODE_system.cpp
        ${Source_dir}/ODE_solver.cpp ${Source_dir}/input.cpp)
set(Headers ${Include_dir}/ODE_system.h ${Include_dir}/ODE_solver.h
        ${Include_dir}/input.h ${Include_dir}/usual_functions.h ${Setting_dir}/user_defined_g.h)
add_executable(test ${Sources} ${Headers})
