#ifndef OED_SOLVER_USUAL_FUNCTIONS_H
#define OED_SOLVER_USUAL_FUNCTIONS_H

#include <cmath>
#include <vector>
#include <iostream>
#include "../include/input.h"

using namespace std;

/// Define double as Real, in case that we need to use float, change the definition of Real here.
typedef double Real;
typedef vector<Real> Vector;
typedef vector<Vector> Matrix;
using namespace std;

/// This function is used to compute the value of a*sin(b*t+c), where a,b,c are given by the user
Real funcsin(Real t,Real a,Real b,Real c){
    return a*sin(b*t+c);
}

/// This function is used to compute the value of a*cos(b*t+c), where a,b,c are given by the user
Real funccos(Real t,Real a,Real b,Real c){
    return a*cos(b*t+c);
}

/// This function is used to compute the value of a*exp(b*t+c), where a,b,c are given by the user
Real funcexp(Real t,Real a,Real b,Real c){
    return a*exp(b*t+c);
}

/// This function is used to compute the value of a*t*t+b*t+c, where a,b,c are given by the user
Real poly(Real t,Real a,Real b,Real c){
    return a*t*t+b*t+c;

}

/// \brief This function is used to compute g(t). Details of g is collected when this function is called for the first time.
Vector usual_fun(Real t){
    /// @param flag: a static variable, initialized to 0, after collecting all the information about g, flag is set to 1.
    static int flag=0;

    /// Define static objects to store unchanged objects during evaluation of the function
    static Matrix allparameters_choice_dim;
    static int dim;
    static Vector choices;

    int choice;
    if (flag != 1) {
        allparameters_choice_dim = Usual_Function_Input();
        /// Extract the dimension from input data matrix
        dim = allparameters_choice_dim.back()[0];

        /// Extract the choices made by user from input data matrix
        choices = allparameters_choice_dim[allparameters_choice_dim.size() - 2];
        flag = 1;
    }

    /// for every dimension, compute the vector g(t) for every t.
    Vector v;
    for (int j = 0; j < dim; ++j) {
        choice = choices[j];
        switch (choice) {
            case 0:
                v.push_back(funcsin(t, allparameters_choice_dim[j][0], allparameters_choice_dim[j][1],
                                    allparameters_choice_dim[j][2]));
                break;
            case 1:
                v.push_back(funccos(t, allparameters_choice_dim[j][0], allparameters_choice_dim[j][1],
                                    allparameters_choice_dim[j][2]));
                break;
            case 2:
                v.push_back(funcexp(t, allparameters_choice_dim[j][0], allparameters_choice_dim[j][1],
                                    allparameters_choice_dim[j][2]));
                break;
            case 3:
                v.push_back(poly(t, allparameters_choice_dim[j][0], allparameters_choice_dim[j][1],
                                 allparameters_choice_dim[j][2]));
                break;
            default:
                cerr << "Unexpected fault!" << endl;
        }
    }
    return v;
};
#endif //ODE_SOLVER_USER_DEFINED_G_H
