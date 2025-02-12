#include "integrator.hpp"
#include <cmath>
#include <array>
/**
 * Template specialization to define weights and points 
 * depending upon the # of points 
 */
template<>
const std::array<double,1> GaussLegendre<1>::weights = 
{2.0};

template<>
const std::array<double,1> GaussLegendre<1>::points = 
{0.0};

template<>
const std::array<double,2> GaussLegendre<2>::weights = 
{1.0,1.0};

template<>
const std::array<double,2> GaussLegendre<2>::points = 
{-1.0/std::sqrt(3),1.0/std::sqrt(3)};

template<>
const std::array<double,3> GaussLegendre<3>::weights = 
{
    5.0/9.0,
    8.0/9.0,
    5.0/9.0,
};

template<>
const std::array<double,3> GaussLegendre<3>::points = 
{
    -std::sqrt(3.0/5.0),
    0.0,
    std::sqrt(3.0/5.0),
};

template<>
const std::array<double,4> GaussLegendre<4>::weights = 
{
    (18.0-std::sqrt(30.0))/36.0,
    (18.0+std::sqrt(30.0))/36.0,
    (18.0+std::sqrt(30.0))/36.0,
    (18.0-std::sqrt(30.0))/36.0,
};

template<>
const std::array<double,4> GaussLegendre<4>::points = 
{
    -std::sqrt((3.0/7.0)+(2.0/7.0)*std::sqrt(6.0/5.0)),
    -std::sqrt((3.0/7.0)-(2.0/7.0)*std::sqrt(6.0/5.0)),
    std::sqrt((3.0/7.0)-(2.0/7.0)*std::sqrt(6.0/5.0)),
    std::sqrt((3.0/7.0)+(2.0/7.0)*std::sqrt(6.0/5.0)),
};




