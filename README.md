# diffyq

A C++ library for solving simple 1st order ordinary differential equations (ODE) and their corresponding initival value problem (IVP). The ODE can be linear or non-linear, homogeneous or non-homogeneous in the format: dy/dt = f(y,t). This library utilizes [exprtk](https://github.com/ArashPartow/exprtk)

This library currently only uses two numerical methods for estimating IVP solutions:
* Predictor Corrector method (c=1/4)
* Adams-Bashforth (2 Step) utilizing the above method
