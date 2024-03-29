//
// Created by pcsc on 11/30/18.
//


#include <iostream>
#include <vector>
#include "../include/ODE_solver.h"
using namespace std;



//f(t,X) = A*X + g(t)
//dim = y00.size()

Vector operator* (Matrix const &A, Vector const &X){
    if(A[0].size() != X.size()){
        throw dimnotmatch();
    };
    Vector result(X.size(),0);
    for (size_t i = 0; i<X.size();i++){
        for(size_t j = 0;j<X.size();j++){
            result[i] += A[i][j] * X[j];
        }
    }
    return result;
}

Vector operator + (Vector const &X, Vector const &Y){
    if(X.size() != Y.size()){
        throw dimnotmatch();
    };
    Vector result(X.size(),0);
    for (size_t i = 0; i < X.size(); i++){
        result[i] = X[i] + Y[i];
    }
    return result;
}

Vector operator- (Vector const &X, Vector const &Y){
    if(X.size() != Y.size()){
        throw dimnotmatch();
    };
    Vector result(X.size(),0);
    for (size_t i = 0; i < X.size(); i++){
        result[i] = X[i] -Y[i];
    }
    return result;
}


Vector operator*(double const& h,Vector const & f){
    int n=f.size();
    Vector rlt;
    for (int i=0;i<n;i++){
        rlt.push_back(h*f[i]);
    }
    return rlt;
}

Real operator*(Vector const& h,Vector const & f){
    int n=f.size();
    Real rlt=0;
    for (int i=0;i<n;i++){
        rlt+=h[i]*f[i];
    }
    return rlt;
}

Matrix ForwardEuler(Real t0, Real tn, Vector const & y00, int M,  Matrix const &A,Vector g(Real)){
    if(M<1){
        throw timesteppositive();
    }
    Real h=(tn-t0)/M;
    Matrix solution;
    Vector f;
    solution.push_back(y00);
    for (int i=0;i<M;++i){
        f=A*solution[i]+g(i*h);
        solution.push_back(solution[i]+h*f);
    }
    return solution;
};


Matrix Adams_Bashforth(Real t0, Real tn, Vector const & y00, int M, int step ,Matrix const &A,Vector g(Real)){
    if(M<1){
        throw timesteppositive();
    }
    Real h=(tn-t0)/M;
    Matrix solution;
    Vector f1;
    Vector f2;
    Vector f3;
    Vector f4;
    Vector f;
    switch (step){
        case 1: return ForwardEuler(t0,tn,y00,M,A,g);
                break;
        case 2:
            solution.push_back(y00);
            f=A*solution[0]+g(t0);
            solution.push_back(solution[0]+h*f);
            for(int i=0;i<M-1;i++){
                f1=A*solution[i]+g(i*h);
                f2=A*solution[i+1]+g((i+1)*h);
                solution.push_back(solution[i+1]+h*(1.5*f2-0.5*f1));
            }
            return solution;
        case 3:
            solution.push_back(y00);
            f=A*solution[0]+g(t0);
            solution.push_back(solution[0]+h*f);
            f=A*solution[1]+g(t0+h);
            solution.push_back(solution[1]+h*f);
            for(int i=0;i<M-2;i++){
                f1=A*solution[i]+g(i*h);
                f2=A*solution[i+1]+g((i+1)*h);
                f3=A*solution[i+2]+g((i+2)*h);
                solution.push_back(solution[i+2]+h*(23.0/12*f3-16.0/12*f2+5.0/12*f1));
            }
            return solution;
        case 4:
            solution.push_back(y00);
            f=A*solution[0]+g(t0);
            solution.push_back(solution[0]+h*f);
            f=A*solution[1]+g(t0+h);
            solution.push_back(solution[1]+h*f);
            f=A*solution[2]+g(t0+2*h);
            solution.push_back(solution[2]+h*f);
            for(int i=0;i<M-3;i++){
                f1=A*solution[i]+g(i*h);
                f2=A*solution[i+1]+g((i+1)*h);
                f3=A*solution[i+2]+g((i+2)*h);
                f4=A*solution[i+3]+g((i+3)*h);
                solution.push_back(solution[i+3]+h*(55.0/24*f4-59.0/24*f3+37.0/24*f2-9.0/24*f1));
            }
            return solution;
        default:
            throw ordernotmatch();
    }
}




Matrix RKSystem4th(Real t0, Real tn, Vector const & y00, int M, Matrix const &A,Vector g(Real)){
    if(M<1){
        throw timesteppositive();
    }
    Real h=(tn-t0)/M;
    Matrix solution;
    solution.push_back(y00);
    Vector k1(y00.size(),0),k2(y00.size(),0),k3(y00.size(),0),k4(y00.size(),0);
    for (int i=0;i<M;i++){
        k1=A*solution[i]+g(i*h);
        k2=A*(solution[i]+0.5*h*k1)+g(i*h+0.5*h);
        k3=A*(solution[i]+0.5*h*k2)+g(i*h+0.5*h);
        k4=A*(solution[i]+h*k3)+g(i*h+h);
       solution.push_back(solution[i]+h*(1.0/6*k1+1.0/3*k2+1.0/3*k3+1.0/6*k4));
    }
    return solution;
}






