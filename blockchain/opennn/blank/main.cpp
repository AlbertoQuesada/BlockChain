/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.artelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   B L A N K   A P P L I C A T I O N                                                                          */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>
#include <algorithm>

#include <stdint.h>
#include <limits.h>

// OpenNN includes

#include "../opennn/opennn.h"

using namespace OpenNN;
using namespace std;

#define N 10000

int main(void)
{
    SparseMatrix<double> sparse_matrix(N,N);
    SparseMatrix<double> sparse_matrix2(sparse_matrix);

    std::cout << "sparse_matrix(0,0) : " << sparse_matrix(0,0) << std::endl;
    std::cout << "sparse_matrix2(0,0) : " << sparse_matrix2(0,0) << std::endl << std::endl;

    double cosa = sparse_matrix(0,0);
    std::cout << "cosa : " << cosa << std::endl;
    std::cout << "rows_indices : " << sparse_matrix.get_rows_indices() << std::endl;
    std::cout << "columns_indices : " << sparse_matrix.get_columns_indices()<< std::endl;
    std::cout << "matrix_values : " << sparse_matrix.get_matrix_values()<< std::endl << std::endl;

    sparse_matrix.set_element(2,1,1);
    const double cosa2 = sparse_matrix(2,1);
    std::cout << "cosa2 : " << cosa2 << std::endl;
    std::cout << "rows_indices : " << sparse_matrix.get_rows_indices() << std::endl;
    std::cout << "columns_indices : " << sparse_matrix.get_columns_indices()<< std::endl;
    std::cout << "matrix_values : " << sparse_matrix.get_matrix_values()<< std::endl << std::endl;

    Matrix<double> dense_matrix(N,N);
    dense_matrix.randomize_normal();
    std::cout << "dense matrix created\n";
    std::cout << "equal operator: " << (sparse_matrix2 == dense_matrix) << std::endl << std::endl;
    dense_matrix.initialize(0);
    dense_matrix(2,1) = 1;
    std::cout << "equal operator: " << (sparse_matrix == dense_matrix) << std::endl << std::endl;

    sparse_matrix2 = sparse_matrix;
//    std::cout << "sparse_matrix:\n" << sparse_matrix << std::endl;
//    std::cout << "sparse_matrix2:\n" << sparse_matrix2 << std::endl;
    std::cout << "equal operator: " << (sparse_matrix == sparse_matrix2) << std::endl << std::endl;

    sparse_matrix.set_element(0,N/2,1);
    sparse_matrix2.set_element(N/2,0,1);
    std::cout << "equal operator: " << (sparse_matrix == sparse_matrix2) << std::endl << std::endl;

    Vector<double> row = sparse_matrix.arrange_row(2);
//    std::cout << "row : " << row << std::endl;
    std::cout << "rows_indices : " << sparse_matrix.get_rows_indices() << std::endl;
    std::cout << "columns_indices : " << sparse_matrix.get_columns_indices()<< std::endl;
    std::cout << "matrix_values : " << sparse_matrix.get_matrix_values()<< std::endl << std::endl;
}




// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2017 Roberto Lopez.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
