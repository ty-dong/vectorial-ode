//
// Created by Jiahua WU on 29.11.18.
//

#include <vector>
#include <iostream>
#include <functional>
#include <string>
#include "ODE_System.h"
#include "ODE_solver.h"
#include "Input.h"
using namespace std;

Vector g(double t){
    Vector result(5,0);
    return result;
}


int main(int argc, char *argv[]){
    string solver_type(argv[2]);
    string setting_path(argv[1]);

    // Read in setting
    Setting_Reader r(setting_path);
    r.read_in();
    Setting s = r.access_setting();

    // Read in matrix and vector
    Vector_Reader v(s.path_y00);
    Matrix_Reader m(s.path_A);
    m.read_in();
    v.read_in();
    Matrix A = m.access_matrix();
    Vector y00 = v.access_vector();

    ODE_System* system;
    if(solver_type == "ForwardEuler"){
        system = new ForwardEuler_System(s.t0,s.tn,y00,A,g,s.M);
        system -> solve();
        system -> write_solution(s.name_of_solution,s.precision,s.delimiter);
    }
    else if(solver_type == "Adams_Bashforth"){
        int step;
        cout << "Please input the step order for Adams Bashforth method" << endl;
        cin >> step;
        system = new Adams_Bashforth_System(s.t0,s.tn,y00,A,g,step,s.M);
        system -> solve();
        system -> write_solution(s.name_of_solution,s.precision,s.delimiter);
    }
    else if(solver_type == "RKSystem4th"){
        system = new RKSystem4th_System(s.t0,s.tn,y00,A,g,s.M);
        system -> solve();
        system -> write_solution(s.name_of_solution,s.precision,s.delimiter);
    }
    else{ cerr << "Invalid Solver type";}

    delete system;
    return 0;
}

