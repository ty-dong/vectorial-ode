//
// Created by Jiahua WU on 23.11.18.
//

#ifndef PROJECT_ODE_SYSTEM_H
#define PROJECT_ODE_SYSTEM_H

#include <vector>
#include <functional>
#include <string>
#include <cassert>
#include "ODE_solver.h"
using namespace std;

template <typename T>
using Vector =  vector<T>;

template <typename T>
using Matrix =  vector<Vector<T> >;

enum Solver_type {FwdEuler, AB, RK4};

template <typename T, int dim>
class ODE_System{
    friend Matrix<T> Adams_Bashforth(double t0, double tn, Vector<T> y00, int M,Vector<T> f(T,Vector<T>));
    friend Matrix<T> ForwardEuler(double t0, double tn, Vector<T> y00, int M,  Vector<T> f(T,Vector<T>));
    friend Matrix<T> RKSystem4th(double t0, double tn, Vector<T> y00, int M, Vector<T> f(T,Vector<T>));
    friend Vector<T> f(T t, Matrix<T> X);

protected:

    double t0; //Initial time
    double tn; //End time

    Vector<T> y00; //Initial condition

    Matrix<T> A;
    Matrix<T> solution;
    function<Vector<T>(T)> g;


public:
    ODE_System(double t0, double tn, Vector<T> y00, Matrix<T> A, Vector<T> g(T)); // Constructor
    ~ODE_System(); // Destructor

    void set_A(const Matrix<T>& A);
    void set_g(Vector<T> g(T));
    void set_y0(const Vector<T>& y0);

    void solve(Solver_type solver_type,int M); // M number of time steps
    void write_solution(string filename,string filetype);
};


//Source code
template <typename T>
Vector<T> operator* (Matrix<T> A, Vector<T> X){
    assert(A[0].size() == X.size());
    Vector<T> result(X.size(),0);
    for (size_t i = 0; i<X.size();i++){
        for(size_t j = 0;j<X.size();j++){
            result[i] += A[i][j] * X[j];
        }
    }
    return result;
}

template <typename T>
Vector <T> operator + (Vector<T> X, Vector<T> Y){
    assert(X.size() == Y.size());
    Vector<T> result(X.size(),0);
    for (size_t i = 0; i < X.size(); i++){
        result[i] = X[i] + Y[i];
    }
    return result;
}

template <typename T,int dim>
ODE_System<T,dim>::ODE_System(double t0, double tn, Vector<T> y00, Matrix<T> A, Vector<T> g(T)):
    A(A), t0(t0),tn(tn),y00(y00),solution(1,y00){
            assert(A.size() == dim and y00.size() == dim);
            ODE_System::g = g;
    }

template <typename T,int dim>
ODE_System<T,dim>::~ODE_System() {
        A.clear();
        solution.clear();
        y00.clear();
}

template <typename T, int dim>
void ODE_System<T,dim>::set_A(const Matrix<T> &other) { A = other; }

template <typename T,int dim>
void ODE_System<T,dim>::set_g(Vector<T> other(T)) { g = other; }

template <typename T,int dim>
void ODE_System<T,dim>::set_y0(const Vector<T> & other) { y00 = other;}

template <typename T,int dim>
Vector<T> f(T t, Matrix<T> X) {return ODE_System<T,dim>::A*X + ODE_System<T,dim>::g(t);}

template <typename T,int dim>
void ODE_System<T,dim>::solve(Solver_type solver_type, int M) {
        switch (solver_type) {
                case FwdEuler: solution = ForwardEuler(t0,tn,y00,M,f);
                case AB: solution = Adams_Bashforth(t0,tn,y00,M,f);
                case RK4: solution = RKSystem4th(t0,tn,y00,M,f);
        }
}

template <typename T, int dim>
void ODE_System<T,dim>::write_solution(string filename, string filetype) {

}


#endif //PROJECT_ODE_SYSTEM_H
