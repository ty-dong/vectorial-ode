


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

/**
 * This class stores essential ingredient of a vectorial ode system as well as a solution
 * obtained by calling specified solver functions.
 */
class ODE_System{

public:

    /** \enum Define Solver types */
    enum Solver_type {FwdEuler, AB, RK4};
    /** \typedef Define the function pointer type */
    typedef Vector(*Funpointer)(Real);

    /** Constructor. Initializes ODE_System data structures*/
    ODE_System(double t0, double tn, Vector y00, Matrix A, Vector g(Real));
    /** Destructor*/
    ~ODE_System();

    /** Accessor to get the solution*/
    Matrix access_solution() const;

    /** Set the Matrix A*/
    void set_A(const Matrix& A);
    /** Set the function g*/
    void set_g(Vector g(Real));
    /** Set initial condition */
    void set_y0(const Vector& y0);

    /**
     * Call the solvers to solve the system and write the solution to member solution\n
     * @param M: number of time steps
     * @param solver_type: enum type including FwdEuler, AB, RK4
     */
    void solve(Solver_type solver_type,int M);

    /**
     * Output the solution as filetype given by the user\n
     * @param precision: number of significant numbers\n
     * @param filetype available: csv, dat,txt
     */
    void write_solution(string filename,string filetype, int precision = 5);

protected:
    /** Initial time*/
    Real t0;
    /** End time*/
    Real tn;

    /** Initial condition*/
    Vector y00;
    /** Function pointer storing the function g as defined in the problem*/
    Funpointer g;
    /** Matrix A as defined in the problem*/
    Matrix A;

    /**
     * Matrix storing the solution\n
     * ith row = solution vector at ith time step\n
     * jth col = solution of the jth component at all time steps
     */
    Matrix solution;
};

#endif //PROJECT_ODE_SYSTEM_H
