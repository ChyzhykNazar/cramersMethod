/*Знайти розв'язок СЛАР методом Крамера*/
/*To find solution for system of linear equation using Cramer's method(Cramer's rule)*/

#include <iostream>
#include <fstream>

using namespace std;

//getting a matrix without i-row rows and j-column
void getMatrix(double** arr, double** p, int i, int j, int m) {
    int di = 0, dj = 0;
    for (int ki = 0; ki < m - 1; ki++) { // check row indexes
        if (ki == i) {
            di = 1;
        }
        for (int kj = 0; kj < m - 1; kj++) { //check column indexes
            if (kj == j) {
                dj = 1;
            }
            p[ki][kj] = arr[ki + di][kj + dj];
        }
        dj = 0;
    }
}

//finding the determinant
double findDeterminant(double** a, int n) {
    int d = 0, j = 0, k = 1, m = n - 1;
    double** p;
    p = new double* [n];
    for (int i = 0; i < n; i++) {
        p[i] = new double[n];
    }
    if (n < 1) {
        cout << "Determinant not founded" << endl;  //if matrix dont have element, so determinant does not exist          
        return d;
    }
    if (n == 1) {
        d = a[0][0];    //determinant is one element
        return d;
    }
    if (n == 2) {
        d = a[0][0] * a[1][1] - (a[1][0] * a[0][1]); // determinannt for matrix 2x2
        return d;
    }
    if (n > 2) {
        for (int i = 0; i < n; i++) {
            getMatrix(a, p, i, 0, n);   //get new matrix
            d = d + k * a[i][0] * findDeterminant(p, m); // calculate the discriminant
            k = -k;
        }
    }
    return d;
}

void cramerMethod(double** a, double* b, double** aa, double* bb, double* x, int n) {
    cout << "___________________________Cramer's method________________________________" << endl;
    double dMain = 0;
    double* d = new double[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = aa[i][j];
        }
        b[i] = bb[i];
    }
    dMain = findDeterminant(a, n);          //calculate the discriminant
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[j][i] = b[j];     //changing column to column of free members
        }
        d[i] = findDeterminant(a, n);       //calculate the discriminant
        for (int j = 0; j < n; j++) {
            a[j][i] = aa[j][i];     //         //overwrite the matrix to the previous state
        }
    }
    for (int i = 0; i < n; i++) {
        x[i] = d[i] / dMain;           //calculate x[i]
        cout << "x[" << i << "] = " << x[i] << " " << endl << endl;       //output of result
    }
}

int main()
{
    int n = 0;
    ifstream file;
    file.open("cramerMethod.txt");
    file >> n;
    double** a;
    double** aa;
    double* b = new double[n];
    double* bb = new double[n];
    double* x = new double[n];
    a = new double* [n];
    aa = new double* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
        aa[i] = new double[n];
    }
    cout << "___________________________Input matrix________________________________" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> a[i][j];
            cout << a[i][j] << " ";
        }
        file >> b[i];
        cout << "|" << b[i] << endl;
    }
    file.close();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aa[i][j] = a[i][j];
        }
        bb[i] = b[i];
    }
    cramerMethod(a, b, aa, bb, x, n);
}