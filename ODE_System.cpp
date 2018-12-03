

/// STL include
#include <vector>
#include <functional>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

/// local include
#include "ODE_solver.h"
#include "ODE_System.h"
using namespace std;

ODE_System::ODE_System(double t0, double tn,const Vector& y00, const Matrix& A, Vector g(Real)):
        A(A), t0(t0),tn(tn),y00(y00),solution(1,y00){
    // Check the match of dimension
    if(A[0].size() != y00.size()) {
        cout << "Warning: Mismatch of dimension between Matrix A and vector variable." << endl;
    }
    // Initialize function pointer
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

void ODE_System::write_solution(string filename, int precision) {
    ofstream outFile;
    outFile.open(filename + ".dat",ios::out);
    // Check if the file is open as expected
    if (!outFile.is_open()){cout << "File open failure. Output is unsuccessful"; return;};

    for (auto vector :solution){
        for (auto value : vector){
            outFile.precision(precision);
            outFile << value << ',';
        }
        outFile << endl;
    }
    outFile.close();
}

ForwardEuler_System::ForwardEuler_System(double t0, double tn,
                                         const Vector& y00, const Matrix& A, Vector g(Real)):
        ODE_System(t0, tn, y00, A, g){}

ForwardEuler_System::~ForwardEuler_System() {
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

void ForwardEuler_System::solve(int M) {
    try {
        solution = ForwardEuler(t0,tn,y00,M,A,g);
    } catch (timesteppossitive& e1){
        cout << e1.what();
    } catch (dimnotmatch& e2){
        cout << e2.what();
    }
}

Adams_Bashforth_System::Adams_Bashforth_System(double t0, double tn,
                                               const Vector& y00,const Matrix& A, Vector g(Real), int step):
        ODE_System(t0, tn, y00, A, g),step(step){}

Adams_Bashforth_System::~Adams_Bashforth_System() {
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

void Adams_Bashforth_System::solve(int M) {
    try {
        solution = Adams_Bashforth(t0, tn, y00, M, step, A, g);
    } catch (timesteppossitive& e1){
        cout << e1.what();
    } catch (dimnotmatch& e2){
        cout << e2.what();
    } catch (ordernotmatch& e3){
        cout << e3.what();
    }
}

RKSystem4th_System::RKSystem4th_System(double t0, double tn,
                                       const Vector& y00, const Matrix& A, Vector g(Real)):
        ODE_System(t0, tn, y00, A, g){}

RKSystem4th_System::~RKSystem4th_System() {
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

void RKSystem4th_System::solve(int M) {
    try {
        solution = RKSystem4th(t0, tn, y00, M, A, g);
    } catch (timesteppossitive& e1){
        cout << e1.what();
    } catch (dimnotmatch& e2){
        cout << e2.what();
    }
}