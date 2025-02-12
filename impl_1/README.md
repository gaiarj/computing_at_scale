# Build Instructions
Run "\$ cmake . " in the directory with CMakeLists.txt present.\
Run "$ make" in the same directory

# Run Instructions 
To run polynomial_integrate, simply call it from the command line with a single input file name as an argument. \
Ex: "\$ polynomial_integrate.x input_file.txt" \
Results are written to "Integration_results.txt" in the same directory as the executable.

# Input file specifications
polynomial_integrate.x can perform multiple integration problems with a single input file, and will output the results of each problem in the order they are defined in the input file. The input file must contain "blocks" with the following format: \
% -> Marks the beginning of a block \
XXXX -> identifier for quadrature rule \
X.X X.X X.X -> Polynomial coefficients (any number) \
X.X X.X -> Integration bounds \
X -> single int for the number of quadrature points

Anything in between blocks should be ignored until the next '%' symbol. Polynomial coefficients are given in this order:\
C_1 + C_1*x + C_2\*x**2 ... 

The identifiers are as follows:\
GLE (Gauss-Legendre)\
GLO (Gauss-Lobatto)\
CHE1 (Chebyshev Type 1)\
CHE2 (Chebyshev Type 2)

Chebyshev can have an arbitrary # of points, but only points 1-4 and 3-5 are implemented for Gauss-Legendre and Gauss-Lobatto respectively. 
