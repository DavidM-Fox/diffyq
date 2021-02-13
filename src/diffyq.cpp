#include "../inc/diffyq.h"

// ivp class constructor
diffyq::ivp::ivp(std::string t_ivp_string) : m_ivp_string(t_ivp_string)
{
    parse_ivp_string();
}

// ivp class deconstructor
diffyq::ivp::~ivp() {}

// Print class data
void diffyq::ivp::print_data()
{
    std::cout << "RHS: " << this->m_ode_rhs << '\n';
    std::cout << "t0: " << this->m_t0 << '\n';
    std::cout << "y(t0):" << this->m_y0 << '\n';
    std::cout << "method: " << this->m_method << '\n';
    std::cout << "h step: " << this->m_h << std::endl;
}

// Parses ivp string into its component fields
void diffyq::ivp::parse_ivp_string()
{
    // Remove whitespace from input string
    this->m_ivp_string.erase(
        remove(this->m_ivp_string.begin(), this->m_ivp_string.end(), ' '),
        this->m_ivp_string.end());

    /*
     *  regex for:
     *      y'(t) = f(y, t)
     *      y(t0) = y_0
     *      method = XYZ
     *      h = FLOAT
     */
    std::regex eq_expr("[a-zA-Z]['][=][a-zA-Z-+()*^0-9\\/]*");
    std::regex ic_expr("[a-zA-Z][(][0-9][)][=][0-9]");
    std::regex m_expr("method[=][a-zA-Z0-9]*");
    std::regex h_expr("h[=][0-9.]*");

    std::smatch eq_match;
    std::smatch ic_match;
    std::smatch m_match;
    std::smatch h_match;

    regex_search(this->m_ivp_string, eq_match, eq_expr);
    regex_search(this->m_ivp_string, ic_match, ic_expr);
    regex_search(this->m_ivp_string, m_match, m_expr);
    regex_search(this->m_ivp_string, h_match, h_expr);

    std::string str_eq = eq_match[0];
    std::string str_ic = ic_match[0];
    std::string str_m = m_match[0];
    std::string str_h = h_match[0];

    // Set right hand side of ODE
    size_t pos = str_eq.find("=");
    this->m_ode_rhs = str_eq.substr(pos + 1, str_eq.length());

    /*
     * Set initial conditions t0 and y0
     * regex for finding t0 and y0 in: y(t0) = y0
     */
    std::regex val_expr("[-+]?([0-9]*\\.[0-9]+|[0-9]+)");
    std::smatch val_match;

    std::stringstream ss;
    std::string::const_iterator search_start(str_ic.cbegin());
    while (regex_search(search_start, str_ic.cend(), val_match, val_expr)) {
        ss << val_match[0] << ' ';
        search_start = val_match.suffix().first;
    }
    ss >> this->m_t0 >> this->m_y0;

    // Set numerical method
    pos = str_m.find("=");
    this->m_method = str_m.substr(pos + 1, str_m.length());

    // Set stepsize 'h'
    pos = str_h.find("=");
    this->m_h = std::stod(str_h.substr(pos + 1, str_h.length()));
}

// PRIVATE: Compiles m_parser for ivp
void diffyq::ivp::diffyq_parse()
{
    this->m_symbol_table.add_variable("y", this->m_y);
    this->m_symbol_table.add_variable("t", this->m_t);
    this->m_symbol_table.add_variable("x", this->m_t);
    this->m_expression.register_symbol_table(this->m_symbol_table);

    // Detect compilation errors of m_parser
    if (!this->m_parser.compile(this->m_ode_rhs, this->m_expression)) {

        printf("Error: %s\tExpression: %s\n", this->m_parser.error().c_str(),
               this->m_ode_rhs.c_str());

        for (std::size_t i = 0; i < this->m_parser.error_count(); ++i) {
            // Include the specific nature of each error
            // and its position in the expression string.

            error_t1 error = this->m_parser.get_error(i);

            printf("Error: %02d Position: %02d "
                   "Type: [%s] "
                   "Message: %s "
                   "Expression: %s\n",
                   static_cast<int>(i), static_cast<int>(error.token.position),
                   exprtk::parser_error::to_str(error.mode).c_str(),
                   error.diagnostic.c_str(), this->m_ode_rhs.c_str());
        }
    }
}

// Estimate y(t) with known y(t0) using the chosen method
double diffyq::ivp::eval(const double &val)
{
    diffyq_parse();
    if (this->m_method == "PC") {
        return method_PC(val);
    }
    else if (this->m_method == "AB2") {
        return method_AB2(val);
    }
    return -1;
}

// Estimate y(t) with PC Method
double diffyq::ivp::method_PC(const double &val)
{
    // Define Yi and Yn
    double Yi = this->m_y0;
    double i = this->m_t0;
    double h = this->m_h;
    double Yn = 0.0;

    double f1, f2;

    // Iterate from t0 to val by stepsize h
    for (i; i <= val; i += h) {
        this->m_t = i;
        this->m_y = Yi;
        f1 = this->m_expression.value();

        this->m_t = i + (2.0 / 3.0) * h;
        this->m_y = Yi + (2.0 / 3.0) * h * f1;
        f2 = this->m_expression.value();
        Yn = Yi + h * (0.25 * f1 + 0.75 * f2);
        Yi = Yn;
    }
    return Yi;
}

// Estimate y(t) with AB2 Method
double diffyq::ivp::method_AB2(const double &val)
{
    // 1 step of a 2nd Order Method is required, using PC(c1=1/4)
    double Y0 = this->m_y0;
    double t0 = this->m_t0;
    double h = this->m_h;
    double val_ab2 = t0 + h;
    double Yi = method_PC(val_ab2);
    double Yn = 0.0;
    double f1, f2;

    // Iterate from t0+h to val by stepsize h
    for (double i = t0 + h; i <= val; i += h) {
        this->m_t = i;
        this->m_y = Yi;
        f1 = this->m_expression.value();

        this->m_t = i - h;
        this->m_y = Y0;
        f2 = this->m_expression.value();
        Yn = Yi + 1.5 * h * f1 - 0.5 * h * f2;
        Y0 = Yi;
        Yi = Yn;
    }
    return Yn;
}