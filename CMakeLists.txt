cmake_minimum_required(VERSION 3.1)
project(ODE_Solver)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 14)
# The next lines represent a list of all the executables in the folder (chapter)
# There is typically one executable per exercise.
# As you solve exercises, you need to add them here.
# The syntax is add_executable(executable_name source_file_name)

set(Sources test.cpp ODE_System.cpp ODE_solver.cpp)
set(Headers ODE_System.h ODE_solver.h)
add_executable(test ${Sources} ${Headers})
