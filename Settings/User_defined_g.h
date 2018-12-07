/**
 * Define g here.
 */

#ifndef ODE_SOLVER_USER_DEFINED_G_H
#define ODE_SOLVER_USER_DEFINED_G_H

#include <cmath>
#include <vector>
using namespace std;

/// Define double as Real, in case that we need to use float, change the definition of Real here.
typedef double Real;
typedef vector<Real> Vector;
typedef vector<Vector> Matrix;

Vector g(Real t){
    Vector v(3,0);
    v[0] = 2 - t;
    v[1] = 0;
    v[2] = 1 - t;
    return v;
};


#endif //ODE_SOLVER_USER_DEFINED_G_H
