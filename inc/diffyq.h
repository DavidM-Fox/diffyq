#ifndef DIFFYQ_H
#define DIFFYQ_H
#include <string>
#include <iostream>
#include <regex>
#include "../inc/exprtk.hpp"

typedef exprtk::symbol_table<double>    symbol_table_t;
typedef exprtk::expression<double>      expression_t;
typedef exprtk::parser<double>          parser_t;
typedef exprtk::parser_error::type      error_t1;

namespace diffyq
{
    class ivp 
    {
        public:
            ivp(std::string t_diffyq_string);
            ~ivp();

            enum method {PC, AB2};

            void print_data();
            double eval(const double &val);

        private:
            void parse_ivp_string();
            void diffyq_parse();

            double method_PC(const double &val);
            double method_AB2(const double &val);
            
            std::string         m_ivp_string;
            std::string         m_ode_rhs;
            std::string         m_method;
            std::string         m_diffyq_string;
            
            double              m_t0;
            double              m_y0;
            double              m_h;
            double              m_y;
            double              m_t;
            
            symbol_table_t      m_symbol_table;
            expression_t        m_expression;
            parser_t            m_parser;
    };
} // namespace diffyq


#endif // !DIFFYQ_H