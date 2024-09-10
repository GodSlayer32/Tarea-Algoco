#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Multiplica dos matrices de tamaño compatible.
 * 
 * La función asume que el número de columnas de la primera matriz (matrixA) es igual al número de filas de la segunda matriz (matrixB).
 * La complejidad del algoritmo es O(n * m * p), donde n es el número de filas de matrixA, m es el número de columnas de matrixA (o filas de matrixB), y p es el número de columnas de matrixB.
 * 
 * @param matrixA Primera matriz de enteros.
 * @param matrixB Segunda matriz de enteros.
 * @return vector<vector<int>> Resultado de la multiplicación de matrixA y matrixB.
 */
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB) {
    int rowsA = matrixA.size();       // Número de filas de la primera matriz.
    int colsA = matrixA[0].size();    // Número de columnas de la primera matriz (y filas de la segunda).
    int colsB = matrixB[0].size();    // Número de columnas de la segunda matriz.

    // Inicializamos la matriz de resultado con ceros.
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    // Multiplicación de matrices
    for (int i = 0; i < rowsA; ++i) {                // Itera sobre las filas de matrixA
        for (int j = 0; j < colsB; ++j) {            // Itera sobre las columnas de matrixB
            for (int k = 0; k < colsA; ++k) {        // Realiza la suma del producto correspondiente
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return result;
}