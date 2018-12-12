//
// Created by Jiahua WU on 08.12.18.
//

#ifndef ODE_SOLVER_USER_DEFINED_G_H
#define ODE_SOLVER_USER_DEFINED_G_H

// To import typedef Vector and Matrix 
#include "../include/ODE_solver.h"

Vector user_define(Real t){
    Vector v;
    v.push_back(sin(3*t-2)+exp(t/100));
    v.push_back(cos(sin(t+3)));
    v.push_back(1/(t*t+1));
    v.push_back(log(t*t+20));
    return v;
};

#endif //ODE_SOLVER_USER_DEFINED_G_H
