#include "inc/diffyq.h"
#include <iostream>

int main(int, char **)
{
    std::string ode("y' = t*2 + (1/y^2), y(1) = 2, method = AB2, h = 0.1");
    diffyq::ivp IVP(ode);
    std::cout << IVP.eval(3) << std::endl;

    return 0;
}