

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


ODE_System::ODE_System(Real t0, Real tn,const Vector& y00, const Matrix& A, Vector g(Real),int M):
        A(A), t0(t0),tn(tn),y00(y00),solution(1,y00),M(M),g(g){
    // Check the match of dimension
    if(A[0].size() != y00.size()) {
        cerr << "Error: Mismatch of dimension between Matrix A and vector variable.\n" << endl;
    }
    // Initialize function pointer
   // ODE_System::g = g;
}

ODE_System::~ODE_System() {
    for (auto& vector : A){
        vector.resize(0);
    }
    A.resize(0);
    solution.resize(0);
    y00.resize(0);
}

Matrix ODE_System::access_solution() const { return solution;}

void ODE_System::write_solution(string filename, int precision, char delimiter) {
    ofstream outFile;
    outFile.open(filename + ".dat",ios::out);
    // Check if the file is open as expected
    if (!outFile.is_open()){cerr << "Error: File open failure. Output is unsuccessful.\n"; return;};

    for (auto vector :solution){
        for (auto value : vector){
            outFile.precision(precision);
            outFile << value << delimiter;
        }
        outFile << endl;
    }
    cout << "Solution is successfully written." << endl ;
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
    } catch (timesteppossitive& e1){
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
    } catch (timesteppossitive& e1){
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
    } catch (timesteppossitive& e1){
        cout << e1.what();
    } catch (dimnotmatch& e2){
        cout << e2.what();
    }
}