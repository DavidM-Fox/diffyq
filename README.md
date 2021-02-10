# diffyq

A C++ library for numerically solving 1st order ordinary differential equations ([ODE](https://en.wikipedia.org/wiki/Ordinary_differential_equation)) with their corresponding initival value problem ([IVP](https://en.wikipedia.org/wiki/Initial_value_problem)). The ODE can be linear or non-linear, homogeneous or non-homogeneous in the format: y' = f(y,t). This library utilizes [exprtk](https://github.com/ArashPartow/exprtk) for expression parsing.

The ivp class takes a comma separated input string with the following required fields:
* ODE: "y'=f(y,t)"
* Initial Condition: "y(t_0) = y_0"
* Numerical Method: "method = XYZ"
* h step: "h = X.X"

Here is an example usage of this library with a minmal main.cpp:

```c++

#include <iostream>
#include "inc/diffyq.h"

int main(int, char**) 
{
  std::string input("y' = t*2 + (1/y^2), y(1) = 2, method = AB2, h = 0.1")
  diffyq::ivp IVP(input);
  std::cout << IVP.eval(3) << std::endl;#include <iostream>

  return 0;
}

```



This library currently uses two numerical methods for estimating IVP solutions:
* [Predictor Corrector method](https://en.wikipedia.org/wiki/Predictor%E2%80%93corrector_method) (c=1/4)
* [Adams-Bashforth](https://en.wikipedia.org/wiki/Linear_multistep_method#Adams%E2%80%93Bashforth_methods) (2 Step) utilizing the above method
