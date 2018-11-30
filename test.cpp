//
// Created by Jiahua WU on 29.11.18.
//

#include <vector>
#include <iostream>
#include "ODE_System.h"
#include "ODE_solver.h"
using namespace std;

Vector g(double t){
    Vector result(5,0);
    return result;
}

int main(){
    vector<double> y00(5,1);
    vector<vector<double > > B(5,y00);
    ODE_System A(0,1,y00,B,g,5);
    cout << B[0][1];
}
