

/// STL include
#include <vector>
#include <functional>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

/// local include
#include "../include/ODE_solver.h"
#include "../include/ODE_system.h"
using namespace std;


ODE_System::ODE_System(Real t0, Real tn,const Vector& y00, const Matrix& A, Vector g(Real),int M):
        A(A), t0(t0),tn(tn),y00(y00),solution(1,y00),M(M),g(g){}

ODE_System::~ODE_System() {
    for (auto& vector : A){
        vector.resize(0);
    }
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

Matrix ODE_System::access_solution() const { return solution;}

void ODE_System::write_solution(string path, int precision, char delimiter) {
    ofstream outFile;
    outFile.open(path,ios::out);
    // Check if the file is open as expected
    if (!outFile.is_open()){throw output_failure();}
    outFile.precision(precision);
    for (auto vector :solution){
        for (size_t i = 0;i<vector.size()-1;++i){
                outFile << vector[i]<< delimiter;
        }
        outFile << vector[vector.size()-1];
        outFile << endl;
    }
    cout << "Solution is successfully written.\n" << endl ;
    outFile.close();
}

ForwardEuler_System::ForwardEuler_System(Real t0, Real tn,
                                         const Vector& y00, const Matrix& A, Vector g(Real), int M):
        ODE_System(t0, tn, y00, A, g, M){}

ForwardEuler_System::~ForwardEuler_System() {
    for (auto& vector : A){
        vector.resize(0);
    }
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

void ForwardEuler_System::solve() {
    try {
        solution = ForwardEuler(t0,tn,y00,M,A,g);
    } catch (timesteppositive& e1){
        cout << e1.what();
    } catch (dimnotmatch& e2){
        cout << e2.what();
    }
}

Adams_Bashforth_System::Adams_Bashforth_System(Real t0, Real tn,
                                               const Vector& y00,const Matrix& A, Vector g(Real), int step, int M):
        ODE_System(t0, tn, y00, A, g,M),step(step){}

Adams_Bashforth_System::~Adams_Bashforth_System() {
    for (auto& vector : A){
        vector.resize(0);
    }
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

void Adams_Bashforth_System::solve() {
    try {
        solution = Adams_Bashforth(t0, tn, y00, M, step, A, g);
    } catch (timesteppositive& e1){
        cout << e1.what();
    } catch (dimnotmatch& e2){
        cout << e2.what();
    } catch (ordernotmatch& e3){
        cout << e3.what();
    }
}

RKSystem4th_System::RKSystem4th_System(Real t0, Real tn,
                                       const Vector& y00, const Matrix& A, Vector g(Real),int M):
        ODE_System(t0, tn, y00, A, g, M){}

RKSystem4th_System::~RKSystem4th_System() {
    for (auto& vector : A){
        vector.resize(0);
    }
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

void RKSystem4th_System::solve() {
    try {
        solution = RKSystem4th(t0, tn, y00, M, A, g);
    } catch (timesteppositive& e1){
        cout << e1.what();
    } catch (dimnotmatch& e2){
        cout << e2.what();
    }
}
