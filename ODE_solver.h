//
// Created by Jiahua WU on 23.11.18.
//

#ifndef PROJECT_ODE_SOLVER_H
#define PROJECT_ODE_SOLVER_H

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

typedef double Real;
typedef vector<Real> Vector;
typedef vector<Vector> Matrix;


//f(t,X) = A*X + g(t)
//dim = y00.size()

Vector operator* (Matrix A, Vector X);

Vector operator + (Vector X, Vector Y);

Vector operator- (Vector X, Vector Y);

Vector operator*(double const h,Vector const & f);

Matrix ForwardEuler(Real t0, Real tn, Vector const & y00, int M, Vector f(Real,Vector));

Matrix Adams_Bashforth(Real t0, Real tn, Vector const & y00, int M, Vector f(Real,Vector),int step);

Matrix RKSystem4th(Real t0, Real tn, Vector const & y00, int M, Vector f(Real,Vector));



#endif //PROJECT_ODE_SOLVER_H


