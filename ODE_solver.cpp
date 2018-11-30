//
// Created by pcsc on 11/30/18.
//

//
// Created by Jiahua WU on 23.11.18.
//



#include <iostream>
#include <vector>
#include <assert.h>
#include <ODE_solver.h>
using namespace std;



//f(t,X) = A*X + g(t)
//dim = y00.size()

Vector operator* (Matrix A, Vector X){
    assert(A[0].size() == X.size());
    Vector result(X.size(),0);
    for (size_t i = 0; i<X.size();i++){
        for(size_t j = 0;j<X.size();j++){
            result[i] += A[i][j] * X[j];
        }
    }
    return result;
}

Vector operator + (Vector X, Vector Y){
    assert(X.size() == Y.size());
    Vector result(X.size(),0);
    for (size_t i = 0; i < X.size(); i++){
        result[i] = X[i] + Y[i];
    }
    return result;
}

Vector operator- (Vector X, Vector Y){
    assert(X.size() == Y.size());
    Vector result(X.size(),0);
    for (size_t i = 0; i < X.size(); i++){
        result[i] = X[i] -Y[i];
    }
    return result;
}


Vector operator*(double const h,Vector const & f){
    int n=f.size();
    Vector rlt;
    for (int i=0;i<n;i++){
        rlt.push_back(h*f[i]);
    }
    return rlt;
}


Matrix ForwardEuler(Real t0, Real tn, Vector const & y00, int M, Vector f(Real,Vector)){
    Real h=(tn-t0)/M;
    Matrix solution;
    solution.push_back(y00);
    for (int i=0;i<M;++i){
        solution.push_back(solution[i]+h*f(i*h,solution[i]));
    }
    return solution;
};


Matrix Adams_Bashforth(Real t0, Real tn, Vector const & y00, int M, Vector f(Real,Vector),int step){
    Real h=(tn-t0)/M;
    Matrix solution;
    switch (step){
        case 1: return ForwardEuler(t0,tn,y00,M,f);
        case 2:
            solution.push_back(y00);
            solution.push_back(y00);
            for(int i=0;i<M-1;i++){
                solution.push_back(solution[i+1]+h*(1.5*f((i+1)*h,solution[i+1])-0.5*f(i*h,solution[i])));
            }
            return solution;
        case 3:
            solution.push_back(y00);
            solution.push_back(y00);
            solution.push_back(y00);
            for(int i=0;i<M-2;i++){
                solution.push_back(solution[i+2]+h*(23.0/12*f((i+2)*h,solution[i+2])
                                                    -16.0/12*f((i+1)*h,solution[i+1])+5.0/12*f(i*h,solution[i])));
            }
            return solution;
        case 4:
            solution.push_back(y00);
            solution.push_back(y00);
            solution.push_back(y00);
            solution.push_back(y00);
            for(int i=0;i<M-3;i++){
                solution.push_back(solution[i+3]+h*(55.0/24*f((i+3)*h,solution[i+3])
                                                    -59.0/24*f((i+2)*h,solution[i+2])+37.0/24*f((i+1)*h,solution[i+1])
                                                    -9.0/24*f(i*h,solution[i])));
            }
            return solution;
        default:
            cout<<"No matching solver!"<<endl;

    }


}




Matrix RKSystem4th(Real t0, Real tn, Vector const & y00, int M, Vector f(Real,Vector)){
    Real h=(tn-t0)/M;
    Matrix solution;
    solution.push_back(y00);
    Vector k1(y00.size(),0),k2(y00.size(),0),k3(y00.size(),0),k4(y00.size(),0);
    for (int i=0;i<M;i++){
        k1=f(i*h,solution[i]);
        k2=f(i*h+0.5*h,solution[i]+h*0.5*k1);
        k3=f(i*h+0.5*h,solution[i]+h*0.5*k2);
        k4=f(i*h+h,solution[i]+h*k3);
        solution.push_back(1.0/6*k1+1.0/3*k2+1.0/3*k3+1.0/6*k4);
    }
    return solution;
}






