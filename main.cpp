#include <iostream>
#include <vector>
#include "inc/diffyq.h"

int main(int, char**) 
{
    std::string diffyq_string = "t*2 + ( 1 / y ^ 2 )";
    double t0 = 1;
    double y0 = 2;
    double t  = 3; 
    double h_step = 0.1;
    diffyq::ivp IVP(diffyq_string);
    IVP.diffyq_solve(t0, y0, t, h_step, IVP.PC);
    IVP.diffyq_solve(t0, y0, t, h_step, IVP.AB2);
}