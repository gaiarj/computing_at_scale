#include "integrator.hpp"
#include <cmath>
#include <array>
/**
 * Template specialization to define weights and points 
 * depending upon the # of points 
 */
template<>
const std::array<double,3> GaussLobatto<3>::weights = {
    1.0/3.0,
    4.0/3.0,
    1.0/3.0,
};

template<>
const std::array<double,3> GaussLobatto<3>::points = {
    -1.0,
    0.0,
    1.0,
};

template<>
const std::array<double,4> GaussLobatto<4>::weights = {
    1.0/6.0,
    5.0/6.0,
    5.0/6.0,
    1.0/6.0,
};

template<>
const std::array<double,4> GaussLobatto<4>::points = {
    -1.0,
    -std::sqrt(1.0/5.0),
    std::sqrt(1.0/5.0),
    1.0,
};

template<>
const std::array<double,5> GaussLobatto<5>::weights = {
    1.0/10.0,
    49.0/90.0,
    32.0/45.0,
    49.0/90.0,
    1.0/10.0,
};

template<>
const std::array<double,5> GaussLobatto<5>::points = {
    -1.0,
    -std::sqrt(3.0/7.0),
    0.0,
    std::sqrt(3.0/7.0),
    1.0,
};

