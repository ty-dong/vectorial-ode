cmake_minimum_required(VERSION 3.1)
project(ODE_Solver)
set(CMAKE_CXX_STANDARD 14)

set(Source_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(Setting_dir ${CMAKE_CURRENT_SOURCE_DIR}/Settings)

set(Sources ${Source_dir}/main.cpp ${Source_dir}/ODE_System.cpp ${Source_dir}/ODE_solver.cpp ${Source_dir}/Input.cpp)
set(Headers ${Include_dir}/ODE_System.h ${Include_dir}/ODE_solver.h ${Include_dir}/Input.h ${Setting_dir}/User_defined_g.h)
add_executable(test ${Sources} ${Headers})
