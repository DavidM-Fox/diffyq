# Diffyq

A C++ library for numerically solving 1st order ordinary differential equations ([ODE](https://en.wikipedia.org/wiki/Ordinary_differential_equation)) with a corresponding initival condition (IC). The ODE can be linear or non-linear, homogeneous or non-homogeneous in the format: y' = f(y,t). [Exprtk](https://github.com/ArashPartow/exprtk) is used for expression parsing.

## Using Diffyq
The library ```diffyq``` consists of a class named ```diffyq::IVP``` that is constructed with a comma separated input string:
* ```diffyq::ivp IVP("{ODE}, {ICS}, {EVAL}, {METHOD}, {HSTEP}")```
* ```diffyq::ivp IVP("y'=f(y,t), y(t0) = y0, method = XYZ, h = X.X");```

The input is saved to ```std::string m_ivp_string``` and then parsed by 5 different regex strings to populate class data:
* ```std::string m_ode_rhs``` = ```"f(y,t)"```
* ```double m_t0``` = ```t0```
* ```double m_y0``` = ```y0```
* ```std::string m_method``` = ```"XYZ"```
* ```double m_h``` = ```X.X```

The user can then call ```IVP.eval(t)``` to estimate y(t) of the ODE's solution.

## Example Usage
Here is an example usage of this library with a minmal main.cpp:

```c++

#include <iostream>
#include "inc/diffyq.h"

int main(int, char**) 
{
  std::string input("y' = t*2 + (1/y^2), y(1) = 2, method = AB2, h = 0.1")
  diffyq::IVP ivp(input);
  std::cout << ivp.eval(3) << std::endl; // IVP.eval(3) returns 10.3582
  return 0;
}

```
This library currently uses two numerical methods for estimating IVP solutions:
* PC - [Predictor Corrector method](https://en.wikipedia.org/wiki/Predictor%E2%80%93corrector_method) (c=1/4)
* AB2 - [Adams-Bashforth](https://en.wikipedia.org/wiki/Linear_multistep_method#Adams%E2%80%93Bashforth_methods) (2 Step) utilizing PC(c=1/4)
