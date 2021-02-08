# diffyq

A C++ library for solving simple 1st order ordinary differential equations ([ODE](https://en.wikipedia.org/wiki/Ordinary_differential_equation)) and their corresponding initival value problem ([IVP](https://en.wikipedia.org/wiki/Initial_value_problem)). The ODE can be linear or non-linear, homogeneous or non-homogeneous in the format: dy/dt = f(y,t). This library utilizes [exprtk](https://github.com/ArashPartow/exprtk) for expression string parsing.

This library currently only uses two numerical methods for estimating IVP solutions:
* [Predictor Corrector method](https://en.wikipedia.org/wiki/Predictor%E2%80%93corrector_method) (c=1/4)
* [Adams-Bashforth](https://en.wikipedia.org/wiki/Linear_multistep_method#Adams%E2%80%93Bashforth_methods) (2 Step) utilizing the above method
