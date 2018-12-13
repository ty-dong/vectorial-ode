
#include <vector>
#include <iostream>
#include <functional>
#include <math.h>
#include "test.h"
#include "./googletest/include/gtest/gtest.h"
#include "../include/ODE_system.h"
#include "../include/ODE_solver.h"
#include "../include/input.h"
#include "../include/usual_functions.h"
#include "settings/user_defined_g.h"
using namespace std;

//test euler forward method.
TEST_F(Eulertest,euler){
   EXPECT_NEAR(residual,0,pow(10,-1));
}

//test adams bashforth method.
TEST_F(ABtest,ab){
    EXPECT_NEAR(residual,0,pow(10,-1)); // adams bashforth order 1
    EXPECT_NEAR(residual1,0,pow(10,-3));// adams bashforth order 2
    EXPECT_NEAR(residual2,0,pow(10,-4));// adams bashforth order 3
    EXPECT_NEAR(residual3,0,pow(10,-4));// adams bashforth order 4
}

//test runge kutta 4th order method.
TEST_F(RK4test,rk4){
    EXPECT_NEAR(residual,0,pow(10,-5));
}

//test the input process; whether A, y00, etc can be read in correctly.
TEST(input_test,c1){
    string setting_path("./settings/setting.dat");
    Setting_Reader r(setting_path);
    r.read_in();
    Setting s = r.access_setting();
    Matrix A1={{1,1,1,1},{1,1,-1,-1},{1,-1,1,-1},{1,-1,-1,-1}};
    Vector y001={1,1,1,1};
    Vector_Reader v(s.path_y00,s.delimiter_data);
    Matrix_Reader m(s.path_A,s.delimiter_data);
    m.read_in();
    v.read_in();
    Matrix A = m.access_matrix();
    Vector y00 = v.access_vector();
    EXPECT_EQ(s.t0,0);
    EXPECT_EQ(s.tn,2);
    EXPECT_EQ(s.M,100);
    EXPECT_EQ(A,A1);
    EXPECT_EQ(y00,y001);
}

//test the operator*: matrix*vector
TEST(matrix_times_vector,c2){
    Matrix A;
    Matrix B;
    Matrix C;
    Vector a(100,0);
    Vector d={1,2,3,4,5,6,7,8,9,10};
    Vector e={10,9,8,7,6,5,4,3,2,1};
    for (int i=0;i<100;i++){
        A.push_back(a);
    }
    Vector b(100,1);
    for (int i=0;i<100;i++){
        B.push_back(b);
    }
    for (int i=0;i<100;i++){
        C.push_back(d);
    }
    Vector f(10,220);
    Vector c(100,100);
    EXPECT_EQ(A*b,a);
    EXPECT_EQ(B*b,c);
    EXPECT_EQ(C*e,f);
// free the memories used
    for (int i=0;i<100;i++){
        A[i].resize(0);
    }
    for (int i=0;i<100;i++){
        B[i].resize(0);
    }
    for (int i=0;i<100;i++){
        C[i].resize(0);
    }
    A.resize(0);
    B.resize(0);
    C.resize(0);
    b.resize(0);
    a.resize(0);
    c.resize(0);
    d.resize(0);
    e.resize(0);
    f.resize(0);
}

//test the operator+ -: vector addition and subtraction
TEST(vector_add_minus,c3){
    Vector a={1,2,3,4,5,6,7,8,9,10};
    Vector b={10,9,8,7,6,5,4,3,2,1};
    Vector c(10,11);
    Vector d={-9,-7,-5,-3,-1,1,3,5,7,9};
    EXPECT_EQ(a+b,c);
    EXPECT_EQ(a-b,d);

}

//test the operator*: vector multiplication
TEST(vector_times_vector,c4){
    Vector a={1,2,3,4,5,6,7,8,9,10};
    Vector b={10,9,8,7,6,5,4,3,2,1};
    EXPECT_EQ(a*b,220);

}

//test the operator*: a constant times a vector
TEST(vector_times_constant,c5){
    Vector a={1,2,3,4,5,6,7,8,9,10};
    Vector b={3,6,9,12,15,18,21,24,27,30};
    EXPECT_EQ(3*a,b);

}

//test the usage of user defined function g
INSTANTIATE_TEST_CASE_P(If_Equal,func_g_test,testing::Range(-100.0,100.0,1.0));
TEST_P(func_g_test,c3){
    Vec_Funpointer g;
    string setting_path("./settings/setting.dat");
    Setting_Reader r(setting_path);
    r.read_in();
    Setting s = r.access_setting();
    switch (s.usual_function){
        case 0: g = user_define; break;
        default: g = usual_fun; break; //If the user define anything other than 0, enter in usual function.
    }
    Real t= GetParam();
    EXPECT_EQ(g(t),user_define_g(t));
}

//test the output process: whether the solution is successfuly written
TEST_F(Eulertest,output){
    euler.write_solution("./solution/solution");
    Matrix_Reader m("./solution/solution",',');
    m.read_in();
    Matrix sln;
    sln=m.access_matrix();
    Vector _residual=sln[100]-euler.access_solution()[100];
    Real _residual1=_residual*_residual;
    EXPECT_NEAR(_residual1,0,pow(10,-6));
}


GTEST_API_ int main(int argc,char** argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
