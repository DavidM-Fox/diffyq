#ifndef DIFFYQ_H
#define DIFFYQ_H
#include "exprtk.hpp"
#include <iostream>
#include <regex>
#include <string>

namespace diffyq {

typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double> expression_t;
typedef exprtk::parser<double> parser_t;
typedef exprtk::parser_error::type error_t1;

class IVP {
public:
    IVP(std::string t_diffyq_string);
    ~IVP();

    double eval(const double &val);
    void printData();

private:
    void parseIvpString();
    void parseDiffyq();

    double methodPC(const double &val);
    double methodAB2(const double &val);

    std::string m_ivp_string;
    std::string m_ode_rhs;
    std::string m_method;
    std::string m_diffyq_string;

    double m_t0;
    double m_y0;
    double m_h;
    double m_y;
    double m_t;

    symbol_table_t m_symbol_table;
    expression_t m_expression;
    parser_t m_parser;
};
} // namespace diffyq

#endif // !DIFFYQ_H