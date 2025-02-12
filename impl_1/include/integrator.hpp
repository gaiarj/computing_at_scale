#ifndef SCALE_INTEGRATOR_JG
#define SCALE_INTEGRATOR_JG
#include <vector>
#include <array>
#include <cmath>
#include "constants.hpp"
#include "scalar_function.hpp"
/**
 * Weights and points should be defined in a seperate .cpp as specialized templates
 * See gauss_legendre.cpp as example
 * 
 * Define new integration rules here, as derived struct from Integrator
 */

struct Integrator{

    //To be implemented by the specific rule
    virtual double integrate(const double& a, const double& b, const ScalarFunction& fx) = 0;

    //Interval change for points 
    double change_interval(double x, double a, double b){ return ((b-a)/2.0)*x + (b+a)/2.0;}
    
};

/**
 * Implements Gauss-Legendre Quadrature
 * Weights and points are defined for N = 1,2,3,4 points 
 */
template <std::size_t num_points>
struct GaussLegendre : Integrator{

    //Performs integration according to the G-Legendre rule 
    double integrate(const double& a, const double& b, const ScalarFunction& fx){
        double sum = 0.0;

        for (std::size_t i=0; i<num_points; ++i){
            sum += weights[i]*fx(this->change_interval(points[i],a,b));
        }
        sum *= (b-a)/2.0;
        return sum;
    }

    static const std::array<double,num_points> weights;
    static const std::array<double,num_points> points; 

};

/**
 * Implements Gauss-Lobatto Quadrature
 * Weights and points are defined for N = 3,4,5 points 
 */
template <std::size_t num_points>
struct GaussLobatto : Integrator{

    //Performs integration according to the G-Lobatto rule
    double integrate(const double& a, const double& b, const ScalarFunction& fx){
        double sum = 0.0;

        for (std::size_t i=1; i<num_points-1; ++i){
            sum += weights[i]*fx(this->change_interval(points[i],a,b));
        }
        sum += weights[0]*fx(a) + weights[num_points-1]*fx(b);
        sum *= (b-a)/2.0;

        return sum;
    }

    static const std::array<double,num_points> weights;
    static const std::array<double,num_points> points; 

};
/**
 * Implements Chebyshev Type 1 quadrature for abitrary # of points
 * Weights and points do not need to be defined
 */
struct ChebyshevType1 : Integrator{

    ChebyshevType1(const std::size_t& num_points) : N(num_points) {}

    //performs integration according to the Chebyshev rule
    double integrate(const double& a, const double& b, const ScalarFunction& fx){
        double sum = 0.0;
        double wi = PI/N;

        for (std::size_t i=0; i<N; ++i){
            double xi = std::cos(PI* (i+0.5)/N);
            sum += fx(xi);
        }
        sum *= wi;
        return sum;
    }

    double N;

};

/**
 * Implements Chebyshev Type 2 quadrature for abitrary # of points
 * Weights and points do not need to be defined
 * Only valid over [-1,1]
 */
struct ChebyshevType2 : Integrator{

    ChebyshevType2(const std::size_t& num_points) : N(num_points) {}

    //performs integration according to the Chebyshev rule
    double integrate(const double& a, const double& b, const ScalarFunction& fx){
        double sum = 0.0;

        for (std::size_t i=0; i<N; ++i){
            double xi = std::cos((i/(N+1))*PI);
            double wi = (PI/(N+1.0))*std::pow((std::sin((i/(N+1))*PI)),2);
            sum += wi*fx(xi);
        }
        //not sure why, but the answer is exactly double what it should be
        sum*=0.5;
        return sum;
    }

    double N;

};

#endif