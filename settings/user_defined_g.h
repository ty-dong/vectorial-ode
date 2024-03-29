//
// Created by Jiahua WU on 08.12.18.
//

#ifndef ODE_SOLVER_USER_DEFINED_G_H
#define ODE_SOLVER_USER_DEFINED_G_H

// To import typedef Vector and Matrix 
#include "../include/ODE_solver.h"

Vector user_define(Real t){
    Vector v;
    v.push_back(2-t);
    v.push_back(0);
    v.push_back(1-t);
    return v;
};

#endif //ODE_SOLVER_USER_DEFINED_G_H
