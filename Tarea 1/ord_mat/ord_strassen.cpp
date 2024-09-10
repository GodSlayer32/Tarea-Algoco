#include <iostream>
#include <vector>

using namespace std;

// Función para sumar dos matrices
// Recibe dos matrices bidimensionales de igual tamaño y devuelve su suma.
// Cada elemento en la posición [i][j] de la matriz resultante es la suma de los elementos en la misma posición de las matrices A y B.
vector<vector<int>> suma(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));  // Inicializar la matriz resultante de suma
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];  // Suma de elementos correspondientes
    return C;
}

// Función para restar dos matrices
// Similar a la función de suma, pero resta los elementos de la segunda matriz de la primera.
vector<vector<int>> resta(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));  // Inicializar la matriz resultante de resta
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];  // Resta de elementos correspondientes
    return C;
}

// Función para dividir una matriz en cuatro submatrices
// Esta función divide la matriz A en cuatro submatrices A11, A12, A21, y A22.
// Esto es útil para algoritmos de multiplicación de matrices que utilizan recursión, como el algoritmo de Strassen.
void dividir(const vector<vector<int>>& A, vector<vector<int>>& A11, vector<vector<int>>& A12,
             vector<vector<int>>& A21, vector<vector<int>>& A22) {
    int n = A.size() / 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A11[i][j] = A[i][j];         // Esquina superior izquierda
            A12[i][j] = A[i][j + n];     // Esquina superior derecha
            A21[i][j] = A[i + n][j];     // Esquina inferior izquierda
            A22[i][j] = A[i + n][j + n]; // Esquina inferior derecha
        }
    }
}

// Función para combinar cuatro submatrices en una sola matriz
// Esta función toma cuatro submatrices y las combina en una matriz más grande.
// Es la operación inversa de 'dividir'.
void combinar(vector<vector<int>>& A, const vector<vector<int>>& A11, const vector<vector<int>>& A12,
              const vector<vector<int>>& A21, const vector<vector<int>>& A22) {
    int n = A11.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = A11[i][j];         // Esquina superior izquierda
            A[i][j + n] = A12[i][j];     // Esquina superior derecha
            A[i + n][j] = A21[i][j];     // Esquina inferior izquierda
            A[i + n][j + n] = A22[i][j]; // Esquina inferior derecha
        }
    }
}

// Función para multiplicar matrices utilizando el algoritmo de Strassen
// Esta función implementa el algoritmo de Strassen para multiplicar dos matrices.
// El algoritmo divide las matrices de entrada en submatrices, calcula productos intermedios,
// y luego combina esos productos para formar la matriz resultante.
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    
    // Caso base: si la matriz es de 1x1, multiplicar los únicos elementos
    if (n == 1) {
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Dividir matrices en submatrices
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

    // Calcular productos intermedios usando recursión
    vector<vector<int>> P1 = strassen(suma(A11, A22), suma(B11, B22));    // P1 = (A11 + A22) * (B11 + B22)
    vector<vector<int>> P2 = strassen(suma(A21, A22), B11);               // P2 = (A21 + A22) * B11
    vector<vector<int>> P3 = strassen(A11, resta(B12, B22));              // P3 = A11 * (B12 - B22)
    vector<vector<int>> P4 = strassen(A22, resta(B21, B11));              // P4 = A22 * (B21 - B11)
    vector<vector<int>> P5 = strassen(suma(A11, A12), B22);               // P5 = (A11 + A12) * B22
    vector<vector<int>> P6 = strassen(resta(A21, A11), suma(B11, B12));   // P6 = (A21 - A11) * (B11 + B12)
    vector<vector<int>> P7 = strassen(resta(A12, A22), suma(B21, B22));   // P7 = (A12 - A22) * (B21 + B22)

    // Calcular submatrices de la matriz resultante
    vector<vector<int>> C11 = suma(resta(suma(P1, P4), P5), P7);  // C11 = P1 + P4 - P5 + P7
    vector<vector<int>> C12 = suma(P3, P5);                      // C12 = P3 + P5
    vector<vector<int>> C21 = suma(P2, P4);                      // C21 = P2 + P4
    vector<vector<int>> C22 = suma(resta(suma(P1, P3), P2), P6); // C22 = P1 + P3 - P2 + P6

    // Combinar submatrices en la matriz resultante
    vector<vector<int>> C(n, vector<int>(n));
    combinar(C, C11, C12, C21, C22);

    return C; // Retornar la matriz resultante de la multiplicación
}
