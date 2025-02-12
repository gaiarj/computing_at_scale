#include "scalar_function.hpp"
#include <vector>
#include <cmath>
/**
 * Class that implements a polynomial function 
 * 
 * Called as PolynomialFunction poly(coef)
 * Where coef is a vector<double> of polynomial coefficients, from low to high order
 * Ex: {0.0 0.0 1.0 2.0} -> 0.0 + 0.0*x + 1.0*x**2 + 2.0*x**3
 * 
 * The operator(double x) is implemented to return the value of the function at the point x 
 */
class PolynomialFunction : public ScalarFunction {
    public:

    PolynomialFunction(const std::vector<double>& coef) :
    coef_(coef) {}
    
    double operator()(double x) const{
        double sum = 0.0;
        for (std::size_t i=0; i<coef_.size(); ++i){
            sum += coef_[i]*(std::pow(x,i));
        }
        return sum;
    }

    std::vector<double> get_coef() {return coef_;}

    private:
    std::vector<double> coef_;
};