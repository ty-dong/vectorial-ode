//
// Created by Jiahua WU on 23.11.18.
//

#ifndef PROJECT_ODE_SYSTEM_H
#define PROJECT_ODE_SYSTEM_H

/// STL include
#include <vector>
#include <functional>
#include <string>
#include <cassert>
#include <iostream>

/// local include
#include "ODE_solver.h"
using namespace std;

/// Define the function pointer type
typedef Vector(*Funpointer)(Real);
/// Define Solver types
enum Solver_type {FwdEuler, AB, RK4};

class ODE_System{

    /// Set solvers as friend functions
    friend Matrix Adams_Bashforth(Real t0, Real tn, Vector const & y00, int M,int step,  Matrix const &A, Vector g(Real));
    friend Matrix ForwardEuler(Real t0, Real tn, Vector const & y00, int M,  Matrix const &A, Vector g(Real));
    friend Matrix RKSystem4th(Real t0, Real tn, Vector const & y00, int M,  Matrix const &A, Vector g(Real));

protected:

    Real t0; /// Initial time
    Real tn; /// End time

    Vector y00; /// Initial condition
    Funpointer g;  /// Function pointer storing the function g as defined in the problem
    Matrix A; /// Matrix A as defined in the problem

    Matrix solution; /// Matrix storing the solution.
                     /// ith row = solution vector at ith time step
                     /// jth col = solution of the jth component at all time steps



public:
    /// Constructor. Initializes ODE_System data structures
    ODE_System(double t0, double tn, Vector y00, Matrix A, Vector g(Real));
    /// Destructor
    ~ODE_System();

    /// Accessor to get the solution
    Matrix access_solution() const;

    /// Set the corresponding members
    void set_A(const Matrix& A);
    void set_g(Vector g(Real));
    void set_y0(const Vector& y0);

    /// Call the solvers to solve the system and write the solution to member solution
    /// M: number of time steps
    void solve(Solver_type solver_type,int M);
    /// Output the solution as filetype given by the user
    /// precision: number of significant numbers
    /// filetype available: csv, dat
    void write_solution(string filename,string filetype, int precision = 5);
};

#endif //PROJECT_ODE_SYSTEM_H
