//
// Created by Jiahua WU on 23.11.18.
//

#ifndef PROJECT_ODE_SYSTEM_H
#define PROJECT_ODE_SYSTEM_H

#include <vector>
#include <array>
#include <string>
#include "ODE_solver.h"
using namespace std;

template <typename T, int dim>
typedef vector<T> Vector;
typedef vector<Vector> Matrix;

typedef Vector (*pfunType)(T);

class ODE_System{

    friend ForwardEuler;
    friend Adams_Bashforth;
    friend RKSystem4th;

private:
    double t0; //Initial time
    double tn; //End time

    Vector y00; //Initial condition

    Matrix A;
    Matrix solution;

    pfunType pg; // function pointer

public:
    ODE_System(int N, double t0, double tn, Vector y00, Matrix A, Matrix solution, Vector g(T)); // Constructor
    ~ODE_System(); // Destructor

    void set_A(const Matrix& A);
    void set g(Vector g(T));
    void set_y0(const Vector& y0);

    void solve(string solver_type,int M); // M number of time steps
    void write_solution(string path,string filetype);
};

#endif //PROJECT_ODE_SYSTEM_H
