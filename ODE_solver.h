//
// Created by Jiahua WU on 23.11.18.
//

#ifndef PROJECT_ODE_SOLVER_H
#define PROJECT_ODE_SOLVER_H

#include <vector>
#include "ODE_System.h"

template <typename T, int dim>
typedef vector<T> Vector;
typedef vector<Vector> Matrix;

Matrix Adams_Bashforth(ODE_System& system, int M);
Matrix ForwardEuler(ODE_System& system, int M);
Matrix RKSystem4th(ODE_System& system, int M);

#endif //PROJECT_ODE_SOLVER_H
