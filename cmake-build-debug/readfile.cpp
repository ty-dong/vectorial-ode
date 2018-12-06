//
// Created by pcsc on 12/1/18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "ODE_System.h"
using namespace std;

ODE_System readfile(){
    ifstream read_file("matrxA.txt");
    assert(read_file.is_open());
    int n;
    Matrix A;
    Real t0,tn;

    read_file>>n;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            read_file>>

        }
    }





}