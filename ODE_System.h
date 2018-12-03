


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

    /** \typedef Define the function pointer type */
    typedef Vector(*Funpointer)(Real);

    /** Constructor. Initializes ODE_System data structures*/
    ODE_System(double t0, double tn, const Vector& y00, const Matrix& A, Vector g(Real));
    /** Destructor. Deallocate memory used by std::vector objects*/
    virtual ~ODE_System();

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
     */
    virtual void solve(int M) = 0;

    /**
     * Output the solution as filetype given by the user\n
     * @param precision: number of significant numbers\n
     * @param filetype available: csv, dat,txt
     */
    void write_solution(string filename,int precision = 5);

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

class ForwardEuler_System : public ODE_System{
public:
    /** Constructor. Initialize data sturcture. */
    ForwardEuler_System(double t0, double tn, const Vector& y00, const Matrix& A, Vector g(Real));

    /** Destructor. Deallocate memory used by std::vector objects*/
    ~ForwardEuler_System () override;

    /** \brief Implement explicit forward euler method.
     * @param t_0:initial time  @param t_n:end time  @param y_00 initial condition @param M number of time steps
     * f(t,y)=A*y+g(t)
     * y_{n+1}=y_n+f(t_n,y_n)*h;
     * @return initial condition and solution after every step are stored in a matrix and returned
     */
    void solve(int M)  override;
};

class Adams_Bashforth_System : public ODE_System{
public:
    /** Constructor. Initialize data sturcture. */
    Adams_Bashforth_System(double t0, double tn, const Vector& y00, const Matrix& A, Vector g(Real),int step);

    /** Destructor. Deallocate memory used by std::vector objects*/
    ~Adams_Bashforth_System() override;

    /** \brief Implement Adams Bashforth method.
     * @param t_0 initial time  @param t_n end time @param y_00 initial condition  @param M number of time steps
     * @param step order of the method,at most 4    f(t,y)=A*y+g(t)
     * step=1: Adams Bashforth method is the same as Forward Euler method.
     * step=2: y_{n+2}=y_{n+1}+h*(3/2*f(t_{n+1},y_{n+1})-1/2*f(t_n,y_n))
     * step=3: y_{n+3}=y_{n+2}+h*(23/12*f(t_{n+2},y_{n+2})-16/12*f(t_{n+1},y_{n+1})+5/12*f(t_n,y_n))
     * step=4: y_{n+4}=y_{n+3}+h*(55/24*f(t_{n+3},y_{n+3})-59/24*f(t_{n+2},y_{n+2})+37/24*f(t_{n+1},y_{n+1})-9/24*f(t_n,y_n))
     * @return initial condition and solution after every step are stored in a matrix and returned
     */
    void solve(int M) override;


protected:
    /** step order of the method */
    int step;
};

class RKSystem4th_System : public ODE_System{
public:
    /** Constructor. Initialize data sturcture.*/
    RKSystem4th_System(double t0, double tn, const Vector& y00,const Matrix& A, Vector g(Real));

    /** Destructor. Deallocate memory used by std::vector objects*/
    ~RKSystem4th_System() override;

    /** \brief Implement Adams Bashforth method.
     * @param t_0 initial time @param t_n end time @param y_00 initial condition  @param M number of time steps
     * f(t,y)=A*y+g(t)
     * k_1=f(t_n,y_n))
     * k_2=f(t_n+0.5*h,y_n+0.5*k_1))
     * k_3=f(t_n+0.5*h,y_n+0.5*k_2))
     * k_4=f(t_n+h,y_n+k_3))
     * y_{n+1}=1/6*k_1+1/3*k_2+1/3*k_3+1/6*k_4
     * @return initial condition and solution after every step are stored in a matrix and returned
     */
    void solve(int M) override;

};
#endif //PROJECT_ODE_SYSTEM_H
