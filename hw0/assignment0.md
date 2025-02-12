# Assignment 0

## (a)
The code was tested by making a small "test suite" which included various cases meant to 
check the error handling and base functionality of the program. These were automated by 
a simple bash script. The testing is limited in the sense that it does not cover 
every possible input case, for example the following items were not tested:
- Matrices with exceptionally large or small values 
- Matrices that are themselves exceptionally large

The tests are summarized as follows:
- Test 1: 5x5 multiplied by a 5x7 matrix. This is to confirm a matrix with one dimension of at least 10 can be read, 
and that the multiplication works for abitrarily sized matrices (as long as they are compatible).
- Test 2: files containing nonsense
- Test 3: non-existent files given as arguments
- Test 4: 3x3 matrix multiplied by a 3x1 vector, result confirmed by symbolab
    - Also tests that the matrix can be read even if the header is missing
- Test 5: 3x3 matrix multipled by a 2x2 matrix, which should give an error
- Test 6: wrong number of command line arguments given

The testing could be vastly improved, and this was just a quick solution. Ideally the script would actually
check that each test produced the expected result, and then summarize that at the end of the output instead of
just running each test and then moving on to the next. Also, I am only testing situations I've already
accounted for. 

## (b)
The matrix market format is not suitable for dense matrices because it includes too much information. 
For a sparse matrix, MMF is helpful because most entries are 0 and therefore writing out the entire matrix
would take up a lot of space with unneccesary data. However, when nearly every entry has a value then
MMF becomes more of a hindrance because it would just be easier to, for example, write out the matrix
as a csv or whitespace delimited text file. 

## (c)
If I knew the matrix sizes at compile time, at the minium I would hardcode the matrix sizes into the 
multiplication function so no time is wasted getting the size of the matrices, or checking that the 
dimensions are compatible. If you really wanted to, you could hand-code the value of every resultant value
instead of looping, but I'm not sure that would increase performance? 

## (d)
My matrix representation was row-major. I choose this because it is my understanding that this 
is the standard way C++ handles 2D arrays or vectors. Also, as far as I can tell, there should
be no performance difference between the two, at least for this application. I did not test
that however. From some reading I did, some guy on stack exchange did claim that column major 
representation has a performance advantage in a specific situation but I didn't read further into it. 

## (e)
I have included docstrings for the file and each function. They describe the inputs, outputs,
and return values. They also describe the usage and functionality.

## (f)
I have tried to include exceptions for a variety of input errors, but in reality
there are many different things that can go wrong with that, so I may not have captured everything.
The handled cases are as follows:
- Invalid file content (partially)
    - The caveat is that any file which can be read, but which doesn't provide the correct format means that
    a [[0],[0]] matrix will be returned, which leads to the error being caught as "matrix dimensions incompatible for multiplication"
    which is techincally true, but not the actual error
    - The code is currently relying on the 3rd entry of the first line to determine how many lines (entries) there will be, but 
    if that value is missing the code still runs but produces nonsense results. 
- File cannot be opened / does not exist
- Invalid # of command line arguments
- Matrix dimensions are incompatible for multiplication
To be honest I am still very confused on how exception handling works in c++

## (g)
I am not aware of any specific limitations in the program for the specific funtionality of 
multiplying 2D matrices and 1D vectors. As mentioned in (a), I have not tested the program
for exceptionally large values or matrix sizes, so I can't be sure what the limits are in that
sense. I have used vectors of doubles, so I am limited to the precision possible with 
double precision floats. 

## (h)
If possible, vectorization of the row x col multiplication step could increase 
performance. I think that flattening the vectors to 1D arrays could also increase
performance but I'm not sure about that. 



