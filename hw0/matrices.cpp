/**
 * Program to perform matrix-matrix and matrix-vector multiplication
 * 
 * Reads input from matrix market format as described at:
 * link
 * %% It is important that the indexes start at 1, not 0
 * 
 * Command line usage is as follows:
 * matrix.x input_file_1 input_file_2
 */

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<double>> m_m_mulitplication(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    /**
     * Function to perform 2D matrix multiplication. It also can perform matrix - vector multiplication, but the
     * vector should be a 2D vector but with only 1 row or column. 
     * 
     * Inputs:
     * matrix1 - the first matrix A
     * matrix2 - the second matrix B
     * ^The inputs are multiplied as matrix1 * matrix2
     * 
     * Returns:
     * result - the result from matrix multiplication in 2D vector form
     */
    using DATA_TYPE = double;
    vector<vector<DATA_TYPE>> result = {{0.},{0.}};
    int m = matrix1.size();
    int n = matrix2[0].size();
    int p = matrix1[0].size();

    //resize result matrix depending on m and n
    result.resize(m);
    for (auto &i : result) {
        i.resize(n);
    }

    //multiply
    for (int j=0; j<m; j++){
        for (int k=0; k<n; k++){
            //result[j][k] = matrix1[row j] x matrix2[col k]
            for (int l=0; l<p; l++){
                result[j][k] += matrix1[j][l]*matrix2[l][k];
                //cout << result[j][k] << ' ';
            }
            
        }
        //cout << '\n';
    }

    return result;
}

vector<vector<double>> read_mmf(string filename) {
    /**
     * Function to read a single input file in MMF format
     * 
     * Comment lines starting with % are ignored, and the function begins reading
     * the numerical lines in the next proceding line after the last %, so there cannot be
     * any blank lines inbetween the data and comment lines.
     * 
     * Inputs:
     * filename - the name of the file to read
     * 
     * Returns:
     * matrix - the matrix in 2D vector form
     */
    using DATA_TYPE = double;
    vector<vector<DATA_TYPE>> matrix = {{0.},{0.}};
    int m, n, entries;

    ifstream input_file;
    input_file.open(filename);
    char pos;
    char buffer1[100];
    bool start=false;
    if (input_file.is_open()){
        //ignore comment lines starting with %
        while (start==false){
            //check if line starts with %
            pos = input_file.peek();
            if (pos == '%'){
                //move to the next line
                input_file.getline(buffer1,100,'\n');
            }
            else {
                //once we reach a non-comment line, move on
                start = true;
            }
        }
        //get the matrix info from the first line
        input_file >> m >> n >> entries;
        cout << "Input file " << filename << " contains a " << m << " by " << n << " matrix" << '\n';
        matrix.resize(m);
        // I don't know what the below means, I got it from stackexchange. It resizes the # of columns 
        for (auto &i : matrix) {
            i.resize(n);
        }
        int x, y;
        DATA_TYPE val;
        //I want a check for double type here, but can't figure out the proper way to check types in this context
        for (int i=0; i < entries; i++) {
            input_file >> x >> y >> val;
            matrix[x-1][y-1] = val;
        }
    }
    else {
        throw runtime_error("Could not open specified input file");
    }
    return matrix;
}



int main(int argc, char** argv) {
    /**
     * Inputs:
     *  argv[1] - string with the name of the first input file
     *  argv[2] - string with the name of the second input file
     * Outputs:
     *  The resultant matrix to the terminal in MMF format
     *  1 file named "output.txt", which contains the resultant matrix/vector in matrix market format
     * Returns:
     *  0 if sucessful
     * Calls:
     * read_mmf() to read the input files
     * m_m_multiplication() to complete the matrix multiplication
     */
    vector<vector<double>> matrix1;
    vector<vector<double>> matrix2;
    vector<vector<double>> result_matrix;

    try {
        if (argc !=3) {
            throw argc;
        }
        // how to check type for string in argv?
    }

    catch(int argc){
        cout << "Incorrect number of arguments, should be 2" << "\n";
        return 1;
    }

    try {
        matrix1 = read_mmf(argv[1]);
        matrix2 = read_mmf(argv[2]);
    }
    catch (const runtime_error& e){
        cout << "Error opening an input file" << '\n';
        return 1;
    }
    
    //I don't understand error handling in C++ at all
    try {
        //check # col in A == # row in B
        if (matrix1[0].size() != matrix2.size()) {
            throw logic_error("test");
        }
    }
    catch (const logic_error& e){
        cout << "Matrix dimensions are incompatible for multiplication" << '\n';
        return 1;
    }

    result_matrix = m_m_mulitplication(matrix1, matrix2);
    int m = result_matrix.size();
    int n = result_matrix[0].size();

    //determine # of non-zero entries
    int count = 0;
    for (int j=0; j < m; j++){
        for (int k=0; k < n; k++){
            if (result_matrix[j][k] != 0){
                count += 1;
            }
        }
    }

    cout << "Result from multiplication in MMF format " << '\n';
    
    //write the result in MMF format to terminal
    cout << m << ' ' << n << ' ' << count << '\n';
    for (int j=0; j<m; j++){
        for (int k=0; k<n; k++){
            cout << ' '   << j+1 << ' ' << k+1 << ' ' << result_matrix[j][k] << '\n';
        }
    }
    return 0;
}