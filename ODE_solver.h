//
// Created by Jiahua WU on 23.11.18.
//

#ifndef PROJECT_ODE_SOLVER_H
#define PROJECT_ODE_SOLVER_H

#include <vector>
using namespace std;

template <typename T>
using Vector =  vector<T>;
template <typename T>
using Matrix =  vector<Vector<T> >;


//f(t,X) = A*X + g(t)
//dim = y00.size()

template <typename T>
Matrix<T> Adams_Bashforth(double t0, double tn, Vector<T> y00, int M, Vector<T> f(T,Vector<T>));

template <typename T>
Matrix<T> ForwardEuler(double t0, double tn, Vector<T> y00, int M, Vector<T> f(T,Vector<T>));

template <typename T>
Matrix<T> RKSystem4th(double t0, double tn, Vector<T> y00, int M, Vector<T> f(T,Vector<T>));


#endif //PROJECT_ODE_SOLVER_H
