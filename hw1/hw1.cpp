#include <iostream>
#include <fstream>
#include <cmath>
#include <assert.h>
#include <iomanip>
using namespace std;

int main(int argc, char** argv) {
    ///////////////////////
    //      FILE I/O    ///
    ///////////////////////
    /*ifstream inFile;
    inFile.open(argv[1]);
    assert(inFile);

    int n;//size of matrix
    inFile >> n;
    double** matrix = new double*[n];
    double** A = new double*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[2 * n];
        A[i] = new double[n];
        matrix[i][n + i] = 1.0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inFile >> matrix[i][j];
            A[i][j] = matrix[i][j];
        }
    }//create [A|I]
    inFile.close();*/
    
    int n;
    cin >> n;
    double** matrix = new double*[n];
    double** A = new double*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[2 * n];
        A[i] = new double[n];
        matrix[i][n + i] = 1.0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
            A[i][j] = matrix[i][j];
        }
    }//create [A|I]
    for (int j = 0; j < n; j++) {
        int pivot = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (matrix[i][j] != 0) {
                if (pivot == -1) {
                    pivot = i;
                    for (int k = 2 * n - 1; k >= j; k--) {
                        matrix[pivot][k] /= matrix[pivot][j];
                    } 
                } else {
                    double multiple = matrix[i][j];
                    for (int k = 0; k < 2 * n; k++) {
                        matrix[i][k] -= multiple * matrix[pivot][k];
                    }
                }
            }
        }
        double* temp = matrix[pivot];
        matrix[pivot] = matrix[j];
        matrix[j] = temp;
    }//calculate [I|A^(-1)]
    double max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double element = 0;//cij | C = A * A^(-1)
            for (int k = 0; k < n; k++) {
                element += A[i][k] * matrix[k][n + j];
            }
            if (i == j && abs(element - 1) > max) {
                max = abs(element - 1);
            } else if (i != j && abs(element) > max) {
                max = abs(element);
            }
        }
    }//calculate error


    ///////////////////////
    //      FILE I/O    ///
    ///////////////////////
    /*ofstream outFile;
    outFile.open("./kkk2.txt");
    outFile << max << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outFile << std::setprecision(9) << matrix[i][n + j] << ' ';
        }
        outFile << endl;
    }
    outFile.close();*/
    
    cout << max << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << std::setprecision(9) << matrix[i][n + j] << ' ';
        }
        cout << endl;
    }
}