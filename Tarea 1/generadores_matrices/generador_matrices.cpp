#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para generar una matriz de tamaño filas x columnas con valores aleatorios
vector<vector<int>> generarMatriz(int filas, int columnas) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = rand() % 10; // Valores aleatorios entre 0 y 9
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

// Función principal
int main() {
    srand(time(0)); // Inicializar la semilla para los números aleatorios

    int numPares = 10; // Número de pares de matrices a generar
    int incremento = 15; // Incremento para aumentar las dimensiones de las matrices
    int base = 10; // Tamaño base inicial

    ofstream archivo("matrices.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return 1;
    }

    for (int i = 0; i < numPares; ++i) {
        // Calcular dimensiones de las matrices
        int n = base + i * incremento; // Filas de la primera matriz
        int m = base + (i + 1) * incremento; // Columnas de la primera matriz y filas de la segunda matriz
        int p = base + (i + 2) * incremento; // Columnas de la segunda matriz

        // Generar las dos matrices
        vector<vector<int>> matriz1 = generarMatriz(n, m);
        vector<vector<int>> matriz2 = generarMatriz(m, p);

        // Escribir dimensiones y las matrices en el archivo
        archivo << "Tamaño de la matriz: " << n << "x" << m << " "<< m <<"x"<< p<<"\n";
        archivo << "Matriz A:\n";
        escribirMatriz(archivo, matriz1);
        archivo << "\nMatriz B:\n";
        escribirMatriz(archivo, matriz2);
        archivo << "\n\n"; // Separador entre pares de matrices
    }

    archivo.close();
    cout << "Matrices generadas y guardadas en 'matrices.txt'." << endl;
    return 0;
}
