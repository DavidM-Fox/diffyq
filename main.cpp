#include <iostream>
#include "inc/diffyq.h"

int main(int, char**) 
{
    std::string ode ("y' = t*2 + (1/y^2), y(1) = 2, method = AB2, h = 0.1");
    diffyq::ivp IVP(ode);
    IVP.print_data();

    std::cout << IVP.eval(3) << std::endl;
    std::cout << IVP.eval(2) << std::endl;
    std::cout << IVP.eval(7) << std::endl;
    std::cout << IVP.eval(9) << std::endl;
    return 0;
}