/**
 * Define g here.
 */

#ifndef ODE_SOLVER_USER_DEFINED_G_H
#define ODE_SOLVER_USER_DEFINED_G_H

#include <cmath>
#include <vector>
#include <iostream>
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
Vector g(Real t){
    /// @param flag a static variable, initialized to 0, after collecting all the information about g, flag is set to 1.
    static int flag=0;
    /// @param allparameters all the parameters of functions (sin, cos, exp, polynomial) all stored in this matrix.
    static Matrix allparameters;
    /// @param choice store the choice of every dimention of function g: 0 for sin, 1 for cos, 2 for exp, 3 for polynomial.
    static vector<int> choice;
    ///@param i the dimension of vector g(t)
    static int i;

    /// flag is initialized as 0, after running the following block, flag is set to 1, so that this block is run only once.
    if (flag!=1){
        cout<<"Please input the dimension of your ODE"<<endl;
        cin>>i;
        Vector parameter(3,0);
        int tmp;
        for (int j=0;j<i;j++){
            cout<<"*************************"<<endl;
            cout<<"Please input your choice of function g (press Enter after the choice of every dimension)"<<endl;
            cout<<"0 a*sin(b*t+c)"<<endl;
            cout<<"1 a*cos(b*t+c)"<<endl;
            cout<<"2 a*exp(b*t+c)"<<endl;
            cout<<"3 a*t^2+b*t+c"<<endl;
            cout<<"4 terminate input process"<<endl;
            cout<<"If none of above meets your need, please define your function g in Settings/User_defined_g.h"<<endl;

            cin>>tmp;
            choice.push_back(tmp);
            switch(tmp){
                case 0:
                    cout<<"Please input the parameters a,b and c of function: a*sin(b*t+c)"<<endl;
                    cin>>parameter[0]>>parameter[1]>>parameter[2];
                    allparameters.push_back(parameter);
                    break;
                case 1:
                    cout<<"Please input the parameters a,b and c of function: a*cos(b*t+c)"<<endl;
                    cin>>parameter[0]>>parameter[1]>>parameter[2];
                    allparameters.push_back(parameter);
                    break;
                case 2:
                    cout<<"Please input the parameters a,b and c of function: a*exp(b*t+c)"<<endl;
                    cin>>parameter[0]>>parameter[1]>>parameter[2];
                    allparameters.push_back(parameter);
                    break;
                case 3:
                    cout<<"Please input the parameters a,b and c of function: a*t^2+b*t+c"<<endl;
                    cin>>parameter[0]>>parameter[1]>>parameter[2];
                    allparameters.push_back(parameter);
                    break;
                case 4:
                    cerr<<"Program terminated!"<<endl;
                    break;
                default:
                    cerr<<"No matching function types!"<<endl;

            }


        }


        flag=1;
    }
    /// for every dimension, compute the vector g(t) for every t.
    Vector v;
    for (int j=0;j<i;++j){
        switch (choice[j]){
            case 0:
                v.push_back(funcsin(t,allparameters[j][0],allparameters[j][1],allparameters[j][2]));
                break;
            case 1:
                v.push_back(funccos(t,allparameters[j][0],allparameters[j][1],allparameters[j][2]));
                break;
            case 2:
                v.push_back(funcexp(t,allparameters[j][0],allparameters[j][1],allparameters[j][2]));
                break;
            case 3:
                v.push_back(poly(t,allparameters[j][0],allparameters[j][1],allparameters[j][2]));
                break;
            default:
                cerr<<"Unexpected fault!"<<endl;

        }
    }

    return v;
};
#endif //ODE_SOLVER_USER_DEFINED_G_H
