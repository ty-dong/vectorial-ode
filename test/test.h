//
// Created by pcsc on 12/6/18.
//

#ifndef ODE_SOLVER_TEST_H
#define ODE_SOLVER_TEST_H
#include <vector>
#include <iostream>
#include <functional>
#include<math.h>
#include "../include/ODE_System.h"
#include "../include/ODE_solver.h"
#include "./googletest/include/gtest/gtest.h"
#include "../Settings/User_defined_g.h"

Vector sln(Real t);
Vector ggtest(Real t){
    Vector v;
    v.push_back(2-t);
    v.push_back(0);
    v.push_back(1-t);
    return v;
}


class testaccuracy:public testing::Test{
protected:
    Vector y00={1,1,1};
    Real t0=0;
    Real tn=2;
    Matrix A={{2,1,-2},{-1,0,0},{1,1,-1}};
    int M=100;
    Vector accuratesln=sln(tn);
    Matrix solution;
    Real residual;
};

class Eulertest:public testaccuracy{
protected:
    ForwardEuler_System euler=ForwardEuler_System(t0,tn,y00,A,ggtest,M);
    void SetUp() override  {
        euler.solve();
        solution=euler.access_solution();
        residual=(solution[M]-accuratesln)*(solution[M]-accuratesln);
    }

};

class ABtest:public testaccuracy{
protected:
    Adams_Bashforth_System ab1=Adams_Bashforth_System(t0,tn,y00,A,ggtest,1,M);
    Adams_Bashforth_System ab2=Adams_Bashforth_System(t0,tn,y00,A,ggtest,2,M);
    Adams_Bashforth_System ab3=Adams_Bashforth_System(t0,tn,y00,A,ggtest,3,M);
    Adams_Bashforth_System ab4=Adams_Bashforth_System(t0,tn,y00,A,ggtest,4,M);
    Real residual1,residual2,residual3;
    void SetUp() override  {
        ab1.solve();
        solution=ab1.access_solution();
        residual=(solution[M]-accuratesln)*(solution[M]-accuratesln);
        ab2.solve();
        solution=ab2.access_solution();
        residual1=(solution[M]-accuratesln)*(solution[M]-accuratesln);
        ab3.solve();
        solution=ab3.access_solution();
        residual2=(solution[M]-accuratesln)*(solution[M]-accuratesln);
        ab4.solve();
        solution=ab4.access_solution();
        residual3=(solution[M]-accuratesln)*(solution[M]-accuratesln);
    }

};

class RK4test:public testaccuracy{
protected:
    RKSystem4th_System rk4=RKSystem4th_System(t0,tn,y00,A,ggtest,M);
    void SetUp() override  {
        rk4.solve();
        solution=rk4.access_solution();
        residual=(solution[M]-accuratesln)*(solution[M]-accuratesln);
    }

};

Vector sln(Real t){
    Vector rlt;
    rlt.push_back(exp(t)+2*sin(t)+cos(t)-1);
    rlt.push_back(-exp(t)+2*cos(t)-sin(t)+t);
    rlt.push_back(2*sin(t)+cos(t));
    return rlt;
}
#endif //ODE_SOLVER_TEST_H
