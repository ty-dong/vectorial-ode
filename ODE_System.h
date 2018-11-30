//
// Created by Jiahua WU on 23.11.18.
//

#ifndef PROJECT_ODE_SYSTEM_H
#define PROJECT_ODE_SYSTEM_H

#include <vector>
#include <functional>
#include <string>
#include <cassert>
#include <iostream>
#include "ODE_solver.h"
using namespace std;

typedef Vector(*Funpointer)(Real);


enum Solver_type {FwdEuler, AB, RK4};

class ODE_System{
    friend Matrix Adams_Bashforth(Real t0, Real tn, Vector const & y00, int M,int step,  Matrix const &A, Vector g(Real));
    friend Matrix ForwardEuler(Real t0, Real tn, Vector const & y00, int M,  Matrix const &A, Vector g(Real));
    friend Matrix RKSystem4th(Real t0, Real tn, Vector const & y00, int M,  Matrix const &A, Vector g(Real));

protected:

    Real t0; //Initial time
    Real tn; //End time

    Vector y00; //Initial condition

    Matrix A;
    Matrix solution;
    Funpointer g;


public:
    ODE_System(double t0, double tn, Vector y00, Matrix A, Vector g(Real), int dim); // Constructor
    ~ODE_System(); // Destructor

    Matrix access_solution() const;

    void set_A(const Matrix& A);
    void set_g(Vector g(Real));
    void set_y0(const Vector& y0);

    void solve(Solver_type solver_type,int M); // M number of time steps
    void write_solution(string filename,string filetype);
};

#endif //PROJECT_ODE_SYSTEM_H
