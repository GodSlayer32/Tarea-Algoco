#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time() para inicializar el generador de números aleatorios
#include <fstream>  // Para escritura en archivos

using namespace std;

// Función para generar una matriz aleatoria
void generarMatrizAleatoria(vector<vector<int>>& matriz, int tamano) {
    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < tamano; ++j) {
            matriz[i][j] = rand() % 100;  // Valores aleatorios entre 0 y 99
        }
    }
}

// Función para imprimir una matriz en un archivo
void imprimirMatriz(ofstream& archivo, const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int valor : fila) {
            archivo << valor << " ";
        }
        archivo << endl;
    }
    archivo << endl;
}

// Función para sumar dos matrices
vector<vector<int>> suma(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Función para restar dos matrices
vector<vector<int>> resta(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Función para dividir una matriz en submatrices
void dividir(const vector<vector<int>>& A, vector<vector<int>>& A11, vector<vector<int>>& A12,
             vector<vector<int>>& A21, vector<vector<int>>& A22) {
    int n = A.size() / 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n];
            A21[i][j] = A[i + n][j];
            A22[i][j] = A[i + n][j + n];
        }
    }
}

// Función para combinar submatrices en una matriz
void combinar(vector<vector<int>>& A, const vector<vector<int>>& A11, const vector<vector<int>>& A12,
              const vector<vector<int>>& A21, const vector<vector<int>>& A22) {
    int n = A11.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = A11[i][j];
            A[i][j + n] = A12[i][j];
            A[i + n][j] = A21[i][j];
            A[i + n][j + n] = A22[i][j];
        }
    }
}

// Función para multiplicar matrices utilizando el algoritmo de Strassen
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int halfSize = n / 2;
    vector<vector<int>> A11(halfSize, vector<int>(halfSize));
    vector<vector<int>> A12(halfSize, vector<int>(halfSize));
    vector<vector<int>> A21(halfSize, vector<int>(halfSize));
    vector<vector<int>> A22(halfSize, vector<int>(halfSize));
    vector<vector<int>> B11(halfSize, vector<int>(halfSize));
    vector<vector<int>> B12(halfSize, vector<int>(halfSize));
    vector<vector<int>> B21(halfSize, vector<int>(halfSize));
    vector<vector<int>> B22(halfSize, vector<int>(halfSize));

    dividir(A, A11, A12, A21, A22);
    dividir(B, B11, B12, B21, B22);

    vector<vector<int>> P1 = strassen(suma(A11, A22), suma(B11, B22));
    vector<vector<int>> P2 = strassen(suma(A21, A22), B11);
    vector<vector<int>> P3 = strassen(A11, resta(B12, B22));
    vector<vector<int>> P4 = strassen(A22, resta(B21, B11));
    vector<vector<int>> P5 = strassen(suma(A11, A12), B22);
    vector<vector<int>> P6 = strassen(resta(A21, A11), suma(B11, B12));
    vector<vector<int>> P7 = strassen(resta(A12, A22), suma(B21, B22));

    vector<vector<int>> C11 = suma(resta(suma(P1, P4), P5), P7);
    vector<vector<int>> C12 = suma(P3, P5);
    vector<vector<int>> C21 = suma(P2, P4);
    vector<vector<int>> C22 = suma(resta(suma(P1, P3), P2), P6);

    vector<vector<int>> C(n, vector<int>(n));
    combinar(C, C11, C12, C21, C22);

    return C;
}
//#####################################################################################################
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
//################################################################################################################
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
//#######################################################################################################
int main() {
    srand(time(0));  // Inicializar el generador de números aleatorios
    //ofstream archivo("resultado_matrices_strassen.txt");  // Abrir el archivo para escribir los resultados
    //ofstream archivo("resultado_matrices_cub.txt");
    ofstream archivo("resultado_matrices_cub_opt.txt");
    //int tamanos[] = {2, 4, 8, 16, 32, 64, 128, 256, 512};  // Diferentes tamaños de matrices para probar 3 casos, strassen, cub, cub_opt
    int tamanos[] = {5, 10, 25, 50, 100, 250, 500, 1000};
    for (int n : tamanos) {
        archivo << "Tamaño de la matriz: " << n << " x " << n << "\n\n";
        vector<vector<int>> A(n, vector<int>(n));
        vector<vector<int>> B(n, vector<int>(n));

        // Generar matrices aleatorias
        generarMatrizAleatoria(A, n);
        archivo << "Matriz A:\n\n";
        imprimirMatriz(archivo, A);

        generarMatrizAleatoria(B, n);
        archivo << "Matriz B:\n\n";
        imprimirMatriz(archivo, B);

        // Medir el tiempo para la multiplicación de matrices con el algoritmo de Strassen
        auto inicio = chrono::high_resolution_clock::now();
        //vector<vector<int>> C = strassen(A, B);
        //vector<vector<int>> C = multiplyMatrices(A, B);
        //vector<vector<int>> C = Mutl_cub_opt(A, B);
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;
        cout<<"Tiempo para multiplicación con algoritmo de Cubica Optimizada: " << duracion.count() << " segundos"<<endl;
        archivo << "Resultado Multiplicación:\n\n";
        imprimirMatriz(archivo, C);
        archivo << "Tiempo para multiplicación con algoritmo de Cubica Optimizada: " << duracion.count() << " segundos\n\n";
    }

    archivo.close();  // Cerrar el archivo
    return 0;
}
