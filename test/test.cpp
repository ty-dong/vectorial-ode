
#include <vector>
#include <iostream>
#include <functional>
#include <math.h>
#include "test.h"
#include "../include/ODE_System.h"
#include "../include/ODE_solver.h"
#include "./googletest/include/gtest/gtest.h"
#include "../include/Usual_functions.h"
using namespace std;

//test euler forward method.
TEST_F(Eulertest,euler){
   EXPECT_NEAR(residual,0,pow(10,-2));
}

TEST_F(ABtest,ab){
    EXPECT_NEAR(residual,0,pow(10,-9));
    EXPECT_NEAR(residual1,0,pow(10,-9));
    EXPECT_NEAR(residual2,0,pow(10,-9));
    EXPECT_NEAR(residual3,0,pow(10,-9));
}

TEST_F(RK4test,rk4){
    EXPECT_NEAR(residual,0,pow(10,-7));
}

GTEST_API_ int main(int argc,char** argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
