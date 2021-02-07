#include <iostream>
#include <vector>
#include "inc/diffyq.h"

int main(int, char**) 
{
    std::string diffyq_string = "t*2"; // ( 1 / y ^ 2 )";
    const std::vector<double> diffyq_ics{1,2};
    double eval = 3;
    double h_step = 0.1;
    diffyq::ivp IVP(diffyq_string);
    IVP.diffyq_solve(1, 2, eval, h_step, IVP.PC);
    IVP.diffyq_solve(1, 2, eval, h_step, IVP.AB2);
}