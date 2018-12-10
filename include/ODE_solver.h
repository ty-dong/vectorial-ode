//
// Created by Jiahua WU on 23.11.18.
//

#ifndef PROJECT_ODE_SOLVER_H
#define PROJECT_ODE_SOLVER_H

#include <iostream>
#include <vector>
#include <exception>
using namespace std;
/// \typedef Define double as Real, in case that we need to use float, change the definition of Real here.
typedef double Real;
typedef vector<Real> Vector;
typedef vector<Vector> Matrix;

///  Inheritance of class exception: deal with dimension incompatible problem
class dimnotmatch:public exception{
public:
   virtual const char* what() const throw(){
        return "When using + - or * between vectors, the dimension of vectors does not match!\n";
   }
};

///  Inheritance of class exception: time step should not be negative or 0
class timesteppositive:public exception{
public:
    virtual const char* what() const throw(){
        return "The input number of time step should be possitive!\n";
    }
};

/// Inheritance of class exception: we can only deal with Adams Bashforth method with order 1 2 3 4
class ordernotmatch:public exception{
public:
    virtual const char* what() const throw(){
        return "Only Adams Bashforth method with order 1,2,3,4 can be called!\n";
    }
};

///  Define operator*: the product of a matrix and a vector.
Vector operator* (Matrix const &A, Vector const &X);

///  Define operator+: the sum of two vectors.
Vector operator + (Vector const &X, Vector const &Y);

///  Define operator-: the difference of two vectors.
Vector operator- (Vector const &X, Vector const &Y);

///  Define operator*: the product of a number and a vector.
Vector operator*(double const &h,Vector const & f);


///  Define operator*: the product of two vectors.
Real operator*(Vector const& h,Vector const & f);

Matrix ForwardEuler(Real t0, Real tn, Vector const & y00, int M,  Matrix const &A,Vector g(Real));
/// \brief Implement explicit forward euler method.
/// @param t_0:initial time  @param t_n:end time  @param y_00 initial condition @param M number of steps
///f(t,y)=A*y+g(t)
///y_{n+1}=y_n+f(t_n,y_n)*h;
///@return initial condition and solution after every step are stored in a matrix and returned

Matrix Adams_Bashforth(Real t0, Real tn, Vector const & y00, int M, int step ,Matrix const & A,Vector g(Real)) ;
/// \brief Implement Adams Bashforth method.
/// @param t_0 initial time  @param t_n end time @param y_00 initial condition  @param M number of steps
/// @param step order of the method,at most 4    f(t,y)=A*y+g(t)
/// step=1: Adams Bashforth method is the same as Forward Euler method.
/// step=2: y_{n+2}=y_{n+1}+h*(3/2*f(t_{n+1},y_{n+1})-1/2*f(t_n,y_n))
/// step=3: y_{n+3}=y_{n+2}+h*(23/12*f(t_{n+2},y_{n+2})-16/12*f(t_{n+1},y_{n+1})+5/12*f(t_n,y_n))
/// step=4: y_{n+4}=y_{n+3}+h*(55/24*f(t_{n+3},y_{n+3})-59/24*f(t_{n+2},y_{n+2})+37/24*f(t_{n+1},y_{n+1})-9/24*f(t_n,y_n))
///@return initial condition and solution after every step are stored in a matrix and returned

Matrix RKSystem4th(Real t0, Real tn, Vector const & y00, int M, Matrix const &A,Vector g(Real));
// \brief Implement Adams Bashforth method.
/// @param t_0 initial time @param t_n end time @param y_00 initial condition  @param M number of steps
/// f(t,y)=A*y+g(t)
/// k_1=f(t_n,y_n))
/// k_2=f(t_n+0.5*h,y_n+0.5*k_1))
/// k_3=f(t_n+0.5*h,y_n+0.5*k_2))
/// k_4=f(t_n+h,y_n+k_3))
/// y_{n+1}=1/6*k_1+1/3*k_2+1/3*k_3+1/6*k_4
///@return initial condition and solution after every step are stored in a matrix and returned

#endif //PROJECT_ODE_SOLVER_H


