/**
 * Created by Jiahua WU on 30.11.18.
 */

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

ODE_System::ODE_System(double t0, double tn, Vector y00, Matrix A, Vector g(Real)):
        A(A), t0(t0),tn(tn),y00(y00),solution(1,y00){
    // Check the match of dimension
    if(A[0].size() != y00.size()) {
        cout << "Mismatch of dimension between Matrix A and vector variable." << endl;
        assert(A[0].size() == y00.size());
    }
    // Initialize function pointer
    ODE_System::g = g;
}

ODE_System::~ODE_System() {
/**
 *  Deallocate memory used by std::vector objects
 */
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
        case FwdEuler:
            try {
                solution = ForwardEuler(t0,tn,y00,M,A,g);break;
            } catch (timesteppossitive& e){
                cout << e.what();
            } catch (dimnotmatch& e){
                cout << e.what();
            }
        case AB:
            try {
                int step;
                cout << "Please input the step";
                cin >> step;
                solution = Adams_Bashforth(t0, tn, y00, M, step, A, g);
                break;
            } catch (timesteppossitive& e){
                cout << e.what();
            } catch (dimnotmatch& e){
                cout << e.what();
            } catch (ordernotmatch& e){
                cout << e.what();
            }
        case RK4: try {
                solution = RKSystem4th(t0, tn, y00, M, A, g);
                break;
            } catch (timesteppossitive& e){
                cout << e.what();
            } catch (dimnotmatch& e){
                cout << e.what();
            }
        default: cout << "Invalid input of solver type. The solution is not updated. "
                         "Please choose one between FwdEuler, AB, RK4" << endl;
        }

}


void ODE_System::write_solution(string filename, string filetype, int precision) {
    ofstream outFile;
    outFile.open(filename + '.' + filetype,ios::out);
    // Check if the file is open as expected
    if (!outFile.is_open()){cout << "File open failure. Output is unsuccessful"; return;};

    bool filetype_supported = (filetype == "csv" or filetype == "txt" or filetype == "dat");
    if (filetype_supported){
        for (size_t i = 0; i<solution.size();i++){
            for (auto value : solution[i]){
                outFile.precision(precision);
                outFile << value << ',';
            }
            outFile << endl;
        }
    }
    else{
        cout << "The filetype given is not supported. Solution was not output. "
                "Please choose between the following filetype: txt, dat, csv" << endl;
    }
    outFile.close();
}

