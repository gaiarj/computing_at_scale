cmake_minimum_required(VERSION 3.28.3)
project (numerical_integration CXX)

include_directories(numerical_integration PRIVATE ${PROJECT_SOURCE_DIR}/include )

set (LIBRARY_SOURCES
    src/gauss_legendre.cpp
    src/gauss_lobatto.cpp
    include/integrator.hpp
    include/constants.hpp
    include/scalar_function.hpp
    include/poly_function.hpp)

add_library(integration_library ${LIBRARY_SOURCES})

add_executable(polynomial_integrate.x src/polynomial_integrate.cpp)
target_link_libraries(polynomial_integrate.x integration_library)

add_executable(unit_test.x src/unit_tests.cpp)
target_link_libraries(unit_test.x integration_library)
