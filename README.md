# Vectorial ODE Solver


This projects aims at solving vectorial linear ordinary differential functions:
$$y'(t)=f(t,y)=Ay+g(t),t\in\mathbb{R},y\in\mathbb{R}^n$$ 
using classic solving methods: Euler Forward Method (EFM), Adams-Bashforth Method (order=1,2,3,4) and Runge-Kutta fourth order method. 


|Author|Tianyang Dong|Jiahua Wu|
|---|---|---
|E-mail|tianyang.dong@epfl.ch|jiahua.wu@epfl.ch
----

## Usage
### Obtention of the file

Clone the code pakage from c4science:
```sh
$ git clone ssh://git@c4science.ch/source/ODE_Solver.git
```
The structure of the file is as follows:
```
ODE_Solver
├── CMakeLists.txt
├── Readme.md
├── include
│   ├── ODE_solver.h
│   ├── ODE_system.h
│   ├── input.h
│   └── usual_functions.h
├── settings
│   ├── A.dat
│   ├── setting.dat
│   ├── user_defined_g.h
│   └── y00.dat
├── solution
│   └── solution
└── src
|   ├── ODE_solver.cpp
|   ├── ODE_system.cpp
|   ├── input.cpp
|   └── main.cpp
└──  test
|   ├── test.cpp
|   ├── test.h
|   ├── CMakeLists.txt
|   ├── googletest
└──  Documentation
```
### Setting of parameters
Data needed are read from folder `ODE_Solver/settings`: matrix $$A$$ from `A.dat`, vectorial initial condition $$y_{00}$$ from `y00.dat`, all other preconditions from `setting.dat`. Following the instruction given inside, users can also modify the parameters in `setting.dat` to suit their need.
### Definition of function $$g$$ in RHS
There are two ways to define $$g$$:
- Use the four elementary functions(sin, cos, exponential and quadratic polynomial function) provided by setting the ``usual_function`` option in `setting.dat` to be $$1$$. During execution, choose one of them as well as set the corresponding parameters for each component. 
- Define $$g$$ in `ODE_Solver/settings/user_defined_g.h`, set the option mentionned above to be $$0$$ and recompile the program.

### Execution of the Program
The program is complied using cmake, in the folder cloned from c4science:
````
$ cmake .
$ make
````
An executable file will then be generated. Usage of the program:
```
$ ./ODE_solver [setting-path] [solving-method-name]
```
In our case, to run the program, type
```
$ ./ODE_solver ./settings/setting.dat [solving-method-name]
```
Valid solving method names: ForwardEuler, Adams_Bashforth, RKSystem4th.

### Output of Solution
By default, solution of the ODE system will be automatically written in `ODE_Solver/Solution/solution`. The solution will be in form of a matrix whose rows represent the solution at each step (starting from intial time). Users can specify the path the solution is written to, the precision of the values and the delimiter used in the file in `ODE_Solver/settings/setting.dat`.  

#### 

## Features

  - Implement of Forward Euler method, four steps of Adams Bashforth method and Runge-Kutta 4th order method.
  - Enable user to personalize various parameters including paths of prescribed data, output data path, initial time, end time, number of discretization step,etc.
  - Four options of common elementary functions for g in the right hand side, handily used in terminal and possibility for user to define more complex function in `settings/user_defined_g.h`.

## Test
Google Test is used in the test session. Relative files can be found in the folder `/test`. 
A simple example is used to test the three methods:
$$f(t,y)=Ay+g(t),A=\begin{bmatrix} 2 & 1 & -2 \\ -1 & 0 & 0 \\ 1 & 1 & -1 \end{bmatrix},g(t)=\begin{bmatrix} 2-t \\  0 \\ 1-t \end{bmatrix}$$ 
Initial condition $$y_{00}=\begin{bmatrix} 1 \\  1 \\ 1 \end{bmatrix}$$, initial time $$t_0=0,$$ end time $$t_n=2$$, number of steps $$M=100$$. The solution to this ODE system is 
$$y(t)=e^x\begin{bmatrix} 1 \\  -1 \\ 0 \end{bmatrix}+2\begin{bmatrix} \sin(x) \\  \cos(x) \\ \sin(x) \end{bmatrix}+\begin{bmatrix} \cos(t) \\ -\sin(t) \\ \cos(t) \end{bmatrix}+\begin{bmatrix} -1 \\  t \\ 0 \end{bmatrix}$$
Besides, the input process (whether $$A$$, $$y_{00}$$, other settings are read in successfully), the output process (wthether the solution is written to `/test/solution/solution`), the correctness of vector operators (*, +, -), the usage of function $$g$$ (whether $$g$$ can be read from `/test/settings/user_defined_g.h`) are also tested.
To run the test:
```
$ cmake .
$ make
$ ./test
```
Results of test are as below:

```
[==========] Running 209 tests from 9 test cases.
[----------] Global test environment set-up.
[----------] 2 tests from Eulertest
[ RUN      ] Eulertest.euler
[       OK ] Eulertest.euler (1 ms)
[ RUN      ] Eulertest.output
Solution is successfully written.

[       OK ] Eulertest.output (3 ms)
[----------] 2 tests from Eulertest (4 ms total)

[----------] 1 test from ABtest
[ RUN      ] ABtest.ab
[       OK ] ABtest.ab (4 ms)
[----------] 1 test from ABtest (4 ms total)

[----------] 1 test from RK4test
[ RUN      ] RK4test.rk4
[       OK ] RK4test.rk4 (2 ms)
[----------] 1 test from RK4test (2 ms total)

[----------] 1 test from input_test
[ RUN      ] input_test.c1
[       OK ] input_test.c1 (27 ms)
[----------] 1 test from input_test (27 ms total)

[----------] 1 test from matrix_times_vector
[ RUN      ] matrix_times_vector.c2
[       OK ] matrix_times_vector.c2 (1 ms)
[----------] 1 test from matrix_times_vector (1 ms total)

[----------] 1 test from vector_add_minus
[ RUN      ] vector_add_minus.c3
[       OK ] vector_add_minus.c3 (0 ms)
[----------] 1 test from vector_add_minus (0 ms total)

[----------] 1 test from vector_times_vector
[ RUN      ] vector_times.c4
[       OK ] vector_times.c4 (0 ms)
[----------] 1 test from vector_times (0 ms total)

[----------] 1 test from vector_times_constant
[ RUN      ] vector_times_constant.c5
[       OK ] vector_times_constant.c5 (0 ms)
[----------] 1 test from vector_times_constant (0 ms total)

[----------] 200 tests from If_Equal/func_g_test
[----------] 200 tests from If_Equal/func_g_test (18 ms total)

[----------] Global test environment tear-down
[==========] 209 tests from 9 test cases ran. (56 ms total)
[  PASSED  ] 209 tests.
```
Eulertest, ABtest and RK4test are test suites for the three solving methods.


## TODO

- Support more complex function types of $$g$$, eg: $$t*exp(-t), \sin(\pi t)+3t^2$$
- Implement implicit solving methods, eg: Backward Euler method. 
