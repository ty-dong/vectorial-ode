//
// Created by Jiahua WU on 30.11.18.
//

//Source code
#include <vector>
#include <functional>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

#include "ODE_solver.h"
#include "ODE_System.h"
using namespace std;

ODE_System::ODE_System(double t0, double tn, Vector y00, Matrix A, Vector g(Real),int dim):
        A(A), t0(t0),tn(tn),y00(y00),solution(1,y00){
    assert(A.size() == dim and y00.size() == dim);
    ODE_System::g = g;
}

ODE_System::~ODE_System() {
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

Matrix ODE_System::access_solution() const { return solution;}

void ODE_System::set_A(const Matrix &other) { A = other; }

void ODE_System::set_g(Vector other(Real)) { g = other; }

void ODE_System::set_y0(const Vector & other) { y00 = other;}

void ODE_System::solve(Solver_type solver_type, int M) {
    switch (solver_type) {
        case FwdEuler: solution = ForwardEuler(t0,tn,y00,M,A,g);
        case AB: int step;
                 cout << "Please input the step"; cin >> step;
                 solution = Adams_Bashforth(t0,tn,y00,M,step,A,g);
        case RK4: solution = RKSystem4th(t0,tn,y00,M,A,g);
        default: cout << "Invalid input of solver type, please choose one between FwdEuler, AB, RK4";
    }
}

void ODE_System::write_solution(string filename, string filetype) {

    ofstream outFile;
    outFile.open(filename + '.' + filetype);
    if (filetype == "csv",ios::out){
        for (size_t i = 0; i<solution.size();i++){
            for (auto value : solution[i]){
                outFile << value << ',';
            }
            outFile << endl;
        }
    }
    else if (filetype == "txt",ios::out){
        for (size_t i = 0; i<solution.size();i++){
            for (auto value : solution[i]){
                outFile << value << ' ';
            }
            outFile << endl;
        }
    }
    outFile.close();
}

