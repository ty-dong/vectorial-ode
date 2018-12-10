
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
#include "../settings/user_defined_g.h"
using namespace std;

//test euler forward method.
TEST_F(Eulertest,euler){
   EXPECT_NEAR(residual,0,pow(10,-2));
}

//test adams bashforth method.
TEST_F(ABtest,ab){
    EXPECT_NEAR(residual,0,pow(10,-2));
    EXPECT_NEAR(residual1,0,pow(10,-3));
    EXPECT_NEAR(residual2,0,pow(10,-4));
    EXPECT_NEAR(residual3,0,pow(10,-4));
}

//test runge kutta 4th order method.
TEST_F(RK4test,rk4){
    EXPECT_NEAR(residual,0,pow(10,-5));
}

//test the input process
TEST(input_test,c1){
    string solver_type("ForwardEuler");
    string setting_path("../settings/setting.dat");


    Setting_Reader r(setting_path);
    r.read_in();
    Setting s = r.access_setting();
    Matrix A1={{2,1,-2},{-1,0,0},{1,1,-1}};
    Vector y001={1,1,1};
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

GTEST_API_ int main(int argc,char** argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
