#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <complex>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h> // Essential for Eigen <-> Numpy conversion

// Define a shorthand for complex double
using Complex = std::complex<double>;

Complex permanent_fast(const Eigen::MatrixXcd &A) {
    long n = A.rows();

    if (n == 2) {
        return A(0,0) * A(1,1) + A(0,1) * A(1,0);
    }
    else if (n == 3) {
        return A(0,0) * A(1,1) * A(2,2) + A(0,1)*A(1,2)*A(2,0) + A(0,2)*A(1,0)*A(2,1) +
                A(0,2)*A(1,1)*A(2,0) + A(0,0)*A(1,2)*A(2,1) + A(0,1)*A(1,0)*A(2,2);
    }
    
    else {
        Eigen::RowVectorXcd RowSum = A.colwise().sum(); 
        
        Complex perm = RowSum.prod();
        std::vector<int> RowSigns(n, 1);
        int SignProd = 1;

        long limit = 1LL << (n - 1); 
        
        for (long i = 1; i < limit; i++){
            long k = 0;
            long temp_i = i;
            
            while ((temp_i & 1) == 0){
                k++;
                temp_i >>= 1;
            }
            
            int CurrSign = RowSigns[k+1];

            if (CurrSign == 1){
                RowSum -= 2.0 * A.row(k+1);
                RowSigns[k+1] = -1;
            } else {
                RowSum += 2.0 * A.row(k+1);
                RowSigns[k+1] = 1;
            }
            
            SignProd = -SignProd;
            
            perm += (double)SignProd * RowSum.prod();
        }
        
        return perm / (double)limit;
    }
}

namespace py = pybind11;

PYBIND11_MODULE(permanent_fast, m) {
    m.doc() = "Module for computing the permanent of a complex matrix";
    
    m.def("permanent", &permanent_fast, "Compute the permanent of a complex square matrix",
          py::arg("A"));
}