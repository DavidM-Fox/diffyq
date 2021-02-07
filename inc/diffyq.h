#ifndef DIFFYQ_H
#define DIFFYQ_H
#include <string>
#include <iostream>
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

            void diffyq_solve(
                const double &t0,
                const double &y0,
                const double &t,
                const double &h,
                ivp::method m);

        private:
            void diffyq_parse();

            double method_PC(
                const double &t0,
                const double &y0,
                const double &t,
                const double &h);
            
            double method_AB2(
                const double &t0,
                const double &y0,
                const double &t,
                const double &h);
            
            std::string         m_diffyq_string;
            std::vector<double> m_ics;

            double              m_y;
            double              m_t;
            
            symbol_table_t      m_symbol_table;
            expression_t        m_expression;
            parser_t            m_parser;
    };
} // namespace diffyq


#endif // !DIFFYQ_H