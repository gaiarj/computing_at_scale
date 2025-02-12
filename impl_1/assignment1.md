# Assignment 1

## (a)
The code was tested using unit tests for the different quadratures in unit_test.cpp. Additionally, the driver program
functionality was tested by making a test input file and ensuring the correct results were printed to the output file.
It would be an improvement to include some kind of automated testing for the driver program that would diff the output file
with a reference output file. The tests are limited in the sense that only basic tests were included.

## (b)
The functions and classes are documented in the code with docstrings, and the usage of the driver program is documented in 
README.md, and an example pair of input/output files are provided in /examples

## (c) and (d)
Error handling was mostly left to the driver program, which checks the validity of each integration case as is is read into
the IntegrationRun class, and these errors are caught in main(). Although it might not catch every error case, if the input
doesn't match exactly what is needed, it should give a message that there is an error in the input parameters which should direct
the user to check their input again. This was tested by including errors in the input file and seeing what message would be printed. 
The input files can be read correctly even if a header or nonsense information is included before/between/after information blocks,
as long as those blocks are defined correctly. 

## (e)
Currently the Chebyshev Type 2 quadrature doesn't seem to work properly - it appears to give an answer that is near exactly double what it should, and so right now it is being multiplied by 1/2 to fix that but it isn't clear what the exact issue is. Additionally, from limited testing it seems it needs a very large # of points (~100) to get within a few decimal places of the correct answer, even though the Type 1
quadrature is accurate with far fewer points. 

Another drawback to the current implementation is the use of templates to define the weights and points for the quadratures. It seemed
like a fun idea, but because the template parameters need to be known at compile time, I need to include if/else statements for every 
possible set of points for Gauss-Legendre and Gauss-Lobatto in IntegrationRun. Doesn't seem very DRY to me. 

## (f) 
The performance of IntegrationRun could be improved if the GaussLegendre and GaussLobatto solvers could be called directly
by the number of points instead of needing an if statement for every # of points. 

## (g) 
The operator() of ScalarFunction would need to be modified to allow calling 2D functions like f(x,y). There would need to be a 
way to tell how many dimensions the ScalarFunction has, and then each quadrature rule would need to be updated with a multi-dimensional version as well. 
It could be generic, with a weight calculated for every dimension, so you would have w_x, w_y,... and the interval change would be applied to 
every xi, yi... Then you would sum w_xi * w_yi * F(xi->x, yi->y). I'm not sure if this is the exact method. 

## (h)
ScalarFunction only defines the operator(), so it is up to the users defined function to do with that as it needs. All of the integration rules
should work with any 1D function that is continuous on the interval [a,b], as they just call f(x). The driver program polynomial_integrate.cpp
only works for polynomials though, as it expects to read polynomial coefficients from the input file. Despite this, it is still possible to use it with functions that add to /multiply polynomials, as long as those don't require additional coefficients to be read in. For example: \
c_1 * x + c_2 * x^2 + e^x \
In the above case, e^x could be added to the function as the input doesn't need to change

## (i)
There are multiple ways to do this. One way is to specify an input format that defines the order of operations that occur on a variable 
x, which is read in to a data structure that stores identifiers for those operations. For example, to define (x^2)/(1+cos(x)): \
var x1, x2
x1, square
x2, cos
x2, +1 
x1, divide x2
x, equal x1
x, return \ 
The identifiers would be used to modify the input variable in the order specified somehow. 


