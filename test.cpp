//
// Created by Jiahua WU on 29.11.18.
//

#include <vector>
#include <iostream>
#include "ODE_System.h"
using namespace std;

Vector<int> g(int t){
    vector<int> result(5,0);
    return result;
}

int main(){
    vector<int> y00(5,1);
    vector<vector<int> > B(5,y00);
    ODE_System<int,5> A(0,1,y00,B,g);
    cout << B[0][1];
}
