#include "integrator.hpp"
#include "poly_function.hpp"
#include <iostream>

int test_poly_x2(){
    PolynomialFunction poly({0.0,0.0,1.0});
    double val = poly(2.0);
    if (val == 4.0){
        return 0;
    }
    else {
        return 1;
    }
}

int test_gle_1(){
    PolynomialFunction poly({1.0,1.0});
    double a = -2.0;
    double b = 2.0;
    double expect = 4.0;
    GaussLegendre<1> solver;
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}
int test_gle_2(){
    PolynomialFunction poly({0.0,0.0,1.0});
    double a = -2.0;
    double b = 2.0;
    double expect = 5.33333333333;
    GaussLegendre<2> solver;
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}
int test_gle_3(){
    PolynomialFunction poly({0.0,0.0,1.0});
    double a = -2.0;
    double b = 2.0;
    double expect = 5.33333333333;
    GaussLegendre<3> solver;
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}
int test_gle_4(){
    PolynomialFunction poly({0.0,0.0,1.0});
    double a = -2.0;
    double b = 2.0;
    double expect = 5.33333333333;
    GaussLegendre<4> solver;
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}

int test_glo_3(){
    PolynomialFunction poly({0.0,0.0,1.0});
    double a = -2.0;
    double b = 2.0;
    double expect = 5.33333333333;
    GaussLobatto<3> solver;
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}
int test_glo_4(){
    PolynomialFunction poly({0.0,0.0,1.0});
    double a = -2.0;
    double b = 2.0;
    double expect = 5.33333333333;
    GaussLobatto<4> solver;
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}
int test_glo_5(){
    PolynomialFunction poly({0.0,0.0,1.0});
    double a = -2.0;
    double b = 2.0;
    double expect = 5.33333333333;
    GaussLobatto<5> solver;
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}

//Test Chebysev
int test_che1(){
    PolynomialFunction poly({1.0,-1.0,2.0,-2.0});
    double a = -1.0;
    double b = 1.0;
    double expect = 6.28318526013;
    ChebyshevType1 solver(10);
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}
int test_che2(){
    PolynomialFunction poly({1.0,-1.0,2.0,-2.0});
    double a = -1.0;
    double b = 1.0;
    double expect = 2.35619449019;
    ChebyshevType2 solver(10);
    double integral = solver.integrate(a,b,poly);
    if (std::abs(integral-expect) <= V_TOL){
        return 0;
    }
    else {
        return 1;
    }
}


int main(int argc, char** argv){
    int testsum = 0;

    //Test polynomial
    if (test_poly_x2() == 0){
        std::cout << "test_poly_x2 passes \n";
    } else {
        std::cout << "test_poly_x2 failed \n";
        testsum += 1;
    }

    //Test Gauss Legendre
    if (test_gle_1() == 0){
        std::cout << "test_gle_1 passes \n";
    } else {
        std::cout << "test_gle_1 failed \n";
        testsum += 1;
    }

    if (test_gle_2() == 0){
        std::cout << "test_gle_2 passes \n";
    } else {
        std::cout << "test_gle_2 failed \n";
        testsum += 1;
    }

    if (test_gle_3() == 0){
        std::cout << "test_gle_3 passes \n";
    } else {
        std::cout << "test_gle_3 failed \n";
        testsum += 1;
    }

    if (test_gle_4() == 0){
        std::cout << "test_gle_4 passes \n";
    } else {
        std::cout << "test_gle_4 failed \n";
        testsum += 1;
    }


    //Test GaussLobatto
    if (test_glo_3() == 0){
        std::cout << "test_glo_3 passes \n";
    } else {
        std::cout << "test_glo_3 failed \n";
        testsum += 1;
    }
    if (test_glo_4() == 0){
        std::cout << "test_glo_4 passes \n";
    } else {
        std::cout << "test_glo_4 failed \n";
        testsum += 1;
    }
    if (test_glo_5() == 0){
        std::cout << "test_glo_5 passes \n";
    } else {
        std::cout << "test_glo_5 failed \n";
        testsum += 1;
    }

    //Test Che
    if (test_che1() == 0){
        std::cout << "test_che1 passes \n";
    } else {
        std::cout << "test_che1 failed \n";
        testsum += 1;
    }
    if (test_che2() == 0){
        std::cout << "test_che2 passes \n";
    } else {
        std::cout << "test_che2 failed \n";
        testsum += 1;
    }

    std::cout << testsum << " Tests failed \n";

    return 0;
}