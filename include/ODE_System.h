


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

///  Inheritance of class exception: deal with dimension incompatible problem
class dimmismatch:public exception{
public:
    virtual const char* what() const throw(){
        return "The dimension of vector solution and the constant matrix A does not match!\n";
    }
};

///  Inheritance of class exception: failure of creating an output file
class output_failure:public exception{
public:
    virtual const char* what() const throw(){
        return "The output file fails to be created.\n";
    }
};

/** \brief Define the function pointer type */
typedef Vector(*Vec_Funpointer)(Real);

///This abstract class stores essential ingredients of a vectorial ode system as well as a solution obtained by using specified solver functions.
class ODE_System{

public:

    /** \brief Constructor. Initializes ODE_System data structures*/
    ODE_System(Real t0, Real tn, const Vector& y00, const Matrix& A, Vector g(Real), int M);
    /** \brief Destructor. Deallocate memory used by std::vector objects*/
    virtual ~ODE_System();

    /** \brief Accessor to get the solution*/
    Matrix access_solution() const;

    /**
     * \brief Pure virtual method. Call the solvers to solve the system.
     * @param M: number of time steps
     */
    virtual void solve() = 0;

    /**
     * \brief Output the solution as filetype given by the user\n
     * @param precision: number of significant numbers\n
     * @param filename: name of the file in form of a string\n
     * @param delimiter: character that seperates values
     */
    void write_solution(string filename,int precision = 5, char delimiter = ',');

protected:
    /** \brief Initial time*/
    Real t0;
    /** \brief End time*/
    Real tn;

    /** \brief number of steps*/
    int M;

    /** \brief initial condition*/
    Vector y00;
    /** \brief Function pointer storing the function g as defined in the problem*/
    Vec_Funpointer g;
    /** \brief Matrix A as defined in the problem*/
    Matrix A;

    /**
     * \brief Matrix storing the solution\n
     * ith row = solution vector at ith time step\n
     * jth col = solution of the jth component at all time steps
     */
    Matrix solution;
};

/// Inheritance of class ODE_System: Solving the vectorial system by means of forward Euler method
class ForwardEuler_System : public ODE_System{
public:
    /** \brief Constructor. Initialize data sturcture. */
    ForwardEuler_System(Real t0, Real tn, const Vector& y00, const Matrix& A, Vector g(Real),int M);

    /** \brief Destructor. Deallocate memory used by std::vector objects*/
    ~ForwardEuler_System () override;

    /** \brief Implement explicit forward euler method and store the solution at all time steps in the attribute solution */
    /** f(t,y)=A*y+g(t)\n
     * y_{n+1}=y_n+f(t_n,y_n)*h \n
     * @param M number of steps
     */
    void solve() override;
};

/// Inheritance of class ODE_System: Solving the vectorial system by means of Adams Bashforth method
class Adams_Bashforth_System : public ODE_System{
public:
    /** \brief Constructor. Initialize data sturcture. */
    Adams_Bashforth_System(Real t0, Real tn, const Vector& y00, const Matrix& A, Vector g(Real),int step,int M);

    /** \brief Destructor. Deallocate memory used by std::vector objects*/
    ~Adams_Bashforth_System() override;

    /** \brief Implement Adams Bashforth method and store the solution at all time steps in the attribute solution */
    /** f(t,y)=A*y+g(t)\n
     * step=1: Adams Bashforth method is the same as Forward Euler method. \n
     * step=2: y_{n+2}=y_{n+1}+h*(3/2*f(t_{n+1},y_{n+1})-1/2*f(t_n,y_n)) \n
     * step=3: y_{n+3}=y_{n+2}+h*(23/12*f(t_{n+2},y_{n+2})-16/12*f(t_{n+1},y_{n+1})+5/12*f(t_n,y_n))\n
     * step=4: y_{n+4}=y_{n+3}+h*(55/24*f(t_{n+3},y_{n+3})-59/24*f(t_{n+2},y_{n+2})+37/24*f(t_{n+1},y_{n+1})-9/24*f(t_n,y_n)) \n
     *  @param M number of steps
     */
    void solve() override;


protected:
    /** \brief step order of the method */
    int step;
};

/// Inheritance of class ODE_System: Solving the vectorial system by means of Runge Kutta 4th order method
class RKSystem4th_System : public ODE_System{
public:
    /** \brief Constructor. Initialize data sturcture.*/
    RKSystem4th_System(Real t0, Real tn, const Vector& y00,const Matrix& A, Vector g(Real),int M);

    /** \brief Destructor. Deallocate memory used by std::vector objects*/
    ~RKSystem4th_System() override;

    /** \brief Implement Adams Bashforth method and store the solution at all time steps in the attribute solution */
    /** f(t,y)=A*y+g(t) \n
     * k_1=f(t_n,y_n)) \n
     * k_2=f(t_n+0.5*h,y_n+0.5*k_1)) \n
     * k_3=f(t_n+0.5*h,y_n+0.5*k_2)) \n
     * k_4=f(t_n+h,y_n+k_3)) \n
     * y_{n+1}=1/6*k_1+1/3*k_2+1/3*k_3+1/6*k_4 \n
     * @param M number of steps
     */
    void solve() override;

};

#endif //PROJECT_ODE_SYSTEM_H
