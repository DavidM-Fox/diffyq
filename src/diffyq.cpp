#include "../inc/diffyq.h"


// ivp class constructor
diffyq::ivp::ivp(std::string t_diffyq_string) :
    m_diffyq_string(t_diffyq_string), m_ics(2, 0), m_y(0), m_t(0) { }

// ivp class deconstructor
diffyq::ivp::~ivp() {}

// PRIVATE: Compiles m_parser for ivp
void diffyq::ivp::diffyq_parse()
{
    this->m_symbol_table.add_variable("y", this->m_y);
    this->m_symbol_table.add_variable("t", this->m_t);
    this->m_symbol_table.add_variable("x", this->m_t);
    this->m_expression.register_symbol_table(this->m_symbol_table);

    // Detect compilation errors of m_parser 
    if (!this->m_parser.compile(this->m_diffyq_string,this->m_expression))
    {

        printf
        (
            "Error: %s\tExpression: %s\n",
            this->m_parser.error().c_str(),
            this->m_diffyq_string.c_str()
        );

        for (std::size_t i = 0; i < this->m_parser.error_count(); ++i)
        {
            // Include the specific nature of each error
            // and its position in the expression string.

            error_t1 error = this->m_parser.get_error(i);

            printf("Error: %02d Position: %02d "
                   "Type: [%s] "
                   "Message: %s "
                   "Expression: %s\n",
                   static_cast<int>(i),
                   static_cast<int>(error.token.position),
                   exprtk::parser_error::to_str(error.mode).c_str(),
                   error.diagnostic.c_str(),
                   this->m_diffyq_string.c_str());
        }
    }
}

/*
* Attemps to estimate y(t) with known y(t0) and stepsize h
*/
void diffyq::ivp::diffyq_solve
(
    const double &t0, 
    const double &y0,
    const double &t, 
    const double &h,
    ivp::method m
)
{
    diffyq_parse();

    double ans;
    std::string info;

    switch (m)
    {
    case this->PC:
        ans = method_PC(t0, y0, t, h);
        info = "Estimated with PC:";
        break;
    
    case this->AB2:
        ans = method_AB2(t0, y0, t, h);
        info = "Estimated with AB2:";
        break;
    
    default:
        break;
    }
    
    std::cout << info << ans << '\n';
}

double diffyq::ivp::method_PC(
    const double &t0, 
    const double &y0,
    const double &t, 
    const double &h)
{
    // Define Yi and Yn
	double Yi = y0;
	double Yn = 0.0;

    double f1, f2;

	// From t_start -> t_eval (IC to EVAL)
	for (double i = t0; i <= t; i += h)
    {
        this->m_t = i;
        this->m_y = Yi; 
        f1 = this->m_expression.value();

        this->m_t = i + (2.0/3.0) * h;
        this->m_y = Yi + (2.0/3.0) *h*f1; 
        f2 = this->m_expression.value();

		Yn = Yi + h * (0.25*f1 + 0.75*f2);
		Yi = Yn;
	}

    return Yi;
}

double diffyq::ivp::method_AB2(
    const double &t0, 
    const double &y0,
    const double &t, 
    const double &h)
{
    double f12 = (1.0 / 2.0);
	double f32 = (3.0 / 2.0);


	// 1 step of a 2nd Order Method is required,
	// Will use PC c1=1/4
    double Y0 = y0;
	double Yi = method_PC(t0, y0, t0+h, h);
	double Yn = 0.0;
    double f1, f2;

	// 2-Step AB2 on interval (IC_EVAL[0][1], IC_EVAL[1][1])
	for (double i = t0 + h; i <= t; i += h)
    {
		// Yn = Y1 + f32*h*f(i, Y1) - f12*h*f(i-h, Y0);
        this->m_t = i;
        this->m_y = Yi;
        f1 = this->m_expression.value();
        
        this->m_t = i-h;
        this->m_y = Y0;
        f2 = this->m_expression.value();

		Yn = Yi + 1.5*h*f1 - 0.5*h*f2;
		Y0 = Yi;
		Yi = Yn;
	}
	return Yn;
}

    

