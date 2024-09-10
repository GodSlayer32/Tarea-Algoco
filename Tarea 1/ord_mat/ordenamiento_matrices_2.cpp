#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono> // Para medir el tiempo
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
//#######################################################################################################################################################
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

// Función para leer una matriz del archivo
vector<vector<int>> leerMatriz(ifstream& archivo, int filas, int columnas) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    for (int i = 0; i < filas; ++i) {
        string linea;
        getline(archivo, linea);
        istringstream iss(linea);
        for (int j = 0; j < columnas; ++j) {
            iss >> matriz[i][j];
        }
    }
    return matriz;
}

// Función para escribir una matriz en un archivo
void escribirMatriz(ofstream& archivo, const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (size_t j = 0; j < fila.size(); ++j) {
            archivo << fila[j];
            if (j < fila.size() - 1) archivo << " ";
        }
        archivo << "\n";
    }
}

int main() {
    ifstream archivoEntrada("/home/godslayerdev/Algoco/Tarea 1/generadores_matrices/matrices.txt");
    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return 1;
    }

    ofstream archivoResultado("resultado_multiplicación.txt");
    if (!archivoResultado) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return 1;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
        if (linea.find("Tamaño de la matriz:") != string::npos) {
            // Leer las dimensiones de las matrices
            int n, m, p;
            sscanf(linea.c_str(), "Tamaño de la matriz: %dx%d %dx%d", &n, &m, &m, &p);
            
            // Leer la matriz A
            getline(archivoEntrada, linea); // Leer la línea "Matriz A:"
            vector<vector<int>> matrizA = leerMatriz(archivoEntrada, n, m);

            // Leer la matriz B
            getline(archivoEntrada, linea); // Leer la línea vacía
            getline(archivoEntrada, linea); // Leer la línea "Matriz B:"
            vector<vector<int>> matrizB = leerMatriz(archivoEntrada, m, p);
            auto start = chrono::high_resolution_clock::now();
            
            // Multiplicar matrices A y B
            //vector<vector<int>> resultado = multiplyMatrices(matrizA, matrizB);
            vector<vector<int>> resultado = Mutl_cub_opt(matrizA, matrizB);
            
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            // Escribir el resultado en el archivo
            cout << "Tiempo de ejecución para multiplicar matrices de tamaño " << n << "x" << m << " y " << m << "x" << p << ": " << elapsed.count() << " segundos." << endl;
            archivoResultado << "Resultado de multiplicar matrices de tamaño: " << n << "x" << m << " y " << m << "x" << p << "\n";
            escribirMatriz(archivoResultado, resultado);
            archivoResultado << "\n"; // Separador entre resultados
            
        }
    }

    archivoEntrada.close();
    archivoResultado.close();
    cout << "Multiplicación de matrices completada y guardada en 'resultado_multiplicación.txt'." << endl;
    return 0;
}
