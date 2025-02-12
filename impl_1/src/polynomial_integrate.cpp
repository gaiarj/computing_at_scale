#include "poly_function.hpp"
#include "integrator.hpp"
#include <vector>
#include <cmath>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <stdexcept>
/**
 * Class that stores the information for 
 * performing a single integration operation 
 * for a polynomial function.
 * 
 * The constructor takes
 * std::string rule 
 *  - must be "GLE", "GLO", "CHE1", or "CHE2"
 * std::vector<double> coef : polynomial coefficients
 * double l_bound : lower integration bound
 * double u_bound : upper integration bound
 * std::size_t num_point : Number of quadrature points
 *  - valid inputs for GaussLegendre are 1,2,3,4
 *  - valid inputs for GaussLobatto are 3,4,5
 *  - valid inputs for Chebyshev are any #
 * 
 * Methods are:
 * void solve() : solves the problem according to the input information and stores the result
 * double get_result() : returns the result stored in result_
 */
class IntegrationRun {
public:
    IntegrationRun(const std::vector<double> coef, const double l_bound,
                   const double u_bound, const std::string rule, const std::size_t num_points)
        : coef_(coef), l_bound_(l_bound), u_bound_(u_bound), rule_(rule), num_points_(num_points) {
        if (coef_.empty()) {
            throw std::invalid_argument("Coefficient vector is empty.");
        }
        if (l_bound >= u_bound) {
            throw std::invalid_argument("Lower bound must be less than upper bound.");
        }
        if (num_points_ < 1) {
            throw std::invalid_argument("Number of points must be at least 1.");
        }
        if (rule_ != "GLE" && rule_ != "GLO" && rule_ != "CHE1" && rule_ != "CHE2") {
            throw std::invalid_argument("Integration rule must be 'GLE', 'GLO','CHE1', or 'CHE2'.");
        }
        if (rule_ == "GLE" && coef_.size()-1 > 2*num_points-1){
            throw std::invalid_argument("Gauss-Legendre appoximation is only accurate for polynomials up to degree 2n-1");
        }
        if (rule_ == "GLO" && coef_.size()-1 > 2*num_points_-3){
            throw std::invalid_argument("Gauss-Lobatto approximation is only accurate for polynomials up to degree 2n-3");
        }
    }

    void solve() {
        PolynomialFunction poly(coef_);
        if (rule_ == "GLE") {
            if (num_points_ == 1) {
                auto solver = std::make_unique<GaussLegendre<1>>();
                result_ = solver->integrate(l_bound_, u_bound_, poly);
            } else if (num_points_ == 2) {
                auto solver = std::make_unique<GaussLegendre<2>>();
                result_ = solver->integrate(l_bound_, u_bound_, poly);
            } else if (num_points_ == 3) {
                auto solver = std::make_unique<GaussLegendre<3>>();
                result_ = solver->integrate(l_bound_, u_bound_, poly);
            } else if (num_points_ == 4) {
                auto solver = std::make_unique<GaussLegendre<4>>();
                result_ = solver->integrate(l_bound_, u_bound_, poly);
            } else {
                throw std::invalid_argument("Gauss-Legendre only supports up to 4 points.");
            }
        } else if (rule_ == "GLO"){
            if (num_points_ < 3 || num_points_ > 5) {
                throw std::invalid_argument("Gauss-Lobatto supports 3 to 5 points only.");
            } else if (num_points_== 3) {
                auto solver = std::make_unique<GaussLobatto<3>>();
                result_ = solver->integrate(l_bound_,u_bound_,poly);
                return;
            } else if (num_points_==4){
                auto solver = std::make_unique<GaussLobatto<4>>();
                result_ = solver->integrate(l_bound_,u_bound_,poly);
                return;
            } else if (num_points_==5){
                auto solver = std::make_unique<GaussLobatto<5>>();
                result_ = solver->integrate(l_bound_,u_bound_,poly);
                return;
            }
        } else if (rule_ == "CHE1") {
            if (l_bound_ < -1.0 || u_bound_ > 1.0){
                throw std::invalid_argument("Chebyshev Quadrature is only valid over [-1,1]");
            }
            auto solver = std::make_unique<ChebyshevType1>(num_points_);
            result_ = solver->integrate(l_bound_, u_bound_, poly);
        } else if (rule_ == "CHE2") {
            if (l_bound_ < -1.0 || u_bound_ > 1.0){
                throw std::invalid_argument("Chebyshev Quadrature is only valid over [-1,1]");
            }
            auto solver = std::make_unique<ChebyshevType2>(num_points_);
            result_ = solver->integrate(l_bound_, u_bound_, poly);
        }
    }

    double get_result() const { return result_; }

private:
    std::string rule_;
    std::vector<double> coef_;
    double l_bound_;
    double u_bound_;
    std::size_t num_points_;
    double result_;
};
/**
 * Program to read any # of input integration problems from argv[1] and 
 * print the results in order of their problem definition to "Integration_Results.txt"
 * 
 * Input format is specified in README.md
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::fstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    std::string rule;
    std::string coef;
    std::string bounds;
    std::string N_points;

    std::vector<double> coef_buf;
    std::vector<double> bound_buf;
    std::vector<IntegrationRun> problems;

    while (std::getline(infile, line)) {
        if (line[0] == '%') {
            std::getline(infile, rule);
            std::getline(infile, coef);
            std::istringstream iss(coef);
            double value;
            while (iss >> value) {
                coef_buf.push_back(value);
            }

            std::getline(infile, bounds);
            std::istringstream isb(bounds);
            while (isb >> value) {
                bound_buf.push_back(value);
            }

            std::getline(infile, N_points);
            std::istringstream isn(N_points);
            isn >> value;

            try {
                problems.emplace_back(coef_buf, bound_buf[0], bound_buf[1], rule, static_cast<std::size_t>(value));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error in input parameters: " << e.what() << std::endl;
                return 1;
            }

            coef_buf.clear();
            bound_buf.clear();
        } else if (line == "Stop") {
            break;
        }
    }

    std::vector<double> results;
    for (std::size_t i = 0; i < problems.size(); ++i) {
        try {
            problems[i].solve();
            results.push_back(problems[i].get_result());
        } catch (const std::exception& e) {
            std::cerr << "Error solving problem " << i + 1 << ": " << e.what() << std::endl;
            return 1;
        }
    }

    std::ofstream resultfile("Integration_Results.txt");
    if (!resultfile) {
        std::cerr << "Error opening result file for writing." << std::endl;
        return 1;
    }

    for (std::size_t i = 0; i < results.size(); ++i) {
        resultfile << "Results for problem " << i + 1 << '\n';
        resultfile << results[i] << "\n\n";
    }

    return 0;
}
