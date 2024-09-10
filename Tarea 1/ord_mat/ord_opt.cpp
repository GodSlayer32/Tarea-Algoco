#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Transpone una matriz, intercambiando filas por columnas.
 * 
 * @param matrix Matriz original a transponer.
 * @return vector<vector<int>> Matriz transpuesta.
 */
 
vector<vector<int>> transposeMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> transposed(cols, vector<int>(rows, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

/**
 * @brief Multiplica dos matrices utilizando un algoritmo cúbico optimizado con transposición.
 * 
 * La función multiplica dos matrices de tamaño compatible optimizando el acceso a la memoria mediante
 * la transposición de la segunda matriz para mejorar la eficiencia de la caché.
 * 
 * @param matrixA Primera matriz de enteros de tamaño m x n.
 * @param matrixB Segunda matriz de enteros de tamaño n x p.
 * @return vector<vector<int>> Resultado de la multiplicación de matrixA y matrixB.
 */


vector<vector<int>> Mutl_cub_opt(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) {
    int rowsA = matrixA.size();
    int colsA = matrixA[0].size();
    int colsB = matrixB[0].size();
    vector<vector<int>> transposedB = transposeMatrix(matrixB);
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += matrixA[i][k] * transposedB[j][k];
            }
        }
    }
    return result;
}

