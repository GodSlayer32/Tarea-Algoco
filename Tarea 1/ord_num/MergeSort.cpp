#include <iostream>   // Para operaciones de entrada y salida
#include <fstream>    // Para la manipulación de archivos
#include <vector>     // Para el uso de vectores dinámicos
#include <chrono>     // Para medir tiempos de ejecución
#include <algorithm>  // Incluye algoritmos estándar como std::sort

// Función 'merge' para combinar dos mitades ordenadas de un vector en una sola secuencia ordenada.
// Parámetros:
// - arr: Referencia al vector de enteros que contiene los elementos a ordenar.
// - izquierda: Índice de inicio de la primera mitad del vector.
// - medio: Índice que separa las dos mitades; final de la primera mitad.
// - derecha: Índice de fin de la segunda mitad del vector.
void merge(std::vector<int>& arr, int izquierda, int medio, int derecha) {
    // Calcula el tamaño de las dos mitades a combinar
    int n1 = medio - izquierda + 1; // Tamaño del subvector izquierdo
    int n2 = derecha - medio;       // Tamaño del subvector derecho

    // Crea vectores temporales para almacenar los elementos de las mitades
    std::vector<int> L(n1); // Subvector izquierdo
    std::vector<int> R(n2); // Subvector derecho

    // Copia los elementos del subvector izquierdo al vector temporal L
    for (int i = 0; i < n1; ++i)
        L[i] = arr[izquierda + i];

    // Copia los elementos del subvector derecho al vector temporal R
    for (int j = 0; j < n2; ++j)
        R[j] = arr[medio + 1 + j];

    // Índices iniciales para recorrer L, R y para combinar en el vector arr
    int i = 0;         // Índice para recorrer el subvector L
    int j = 0;         // Índice para recorrer el subvector R
    int k = izquierda; // Índice para colocar los elementos en arr

    // Combinación de los elementos de L y R en arr en orden
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {   // Si el elemento de L es menor o igual al de R
            arr[k] = L[i];    // Coloca L[i] en arr
            ++i;              // Avanza en el subvector L
        } else {
            arr[k] = R[j];    // Coloca R[j] en arr si es menor
            ++j;              // Avanza en el subvector R
        }
        ++k;                  // Avanza en el vector arr
    }

    // Si quedan elementos en L, los copia a arr
    while (i < n1) {
        arr[k] = L[i];        // Copia el elemento de L a arr
        ++i;                  // Avanza en L
        ++k;                  // Avanza en arr
    }

    // Si quedan elementos en R, los copia a arr
    while (j < n2) {
        arr[k] = R[j];        // Copia el elemento de R a arr
        ++j;                  // Avanza en R
        ++k;                  // Avanza en arr
    }
}

// Función 'mergeSort' para ordenar un vector utilizando el algoritmo Merge Sort.
// Parámetros:
// - arr: Referencia al vector de enteros que se desea ordenar.
// - izquierda: Índice de inicio del subvector a ordenar.
// - derecha: Índice de fin del subvector a ordenar.
void mergeSort(std::vector<int>& arr, int izquierda, int derecha) {
    if (izquierda < derecha) {                           // Si el subvector tiene más de un elemento
        int medio = izquierda + (derecha - izquierda) / 2; // Calcula el índice del medio
        mergeSort(arr, izquierda, medio);               // Ordena la mitad izquierda
        mergeSort(arr, medio + 1, derecha);             // Ordena la mitad derecha
        merge(arr, izquierda, medio, derecha);          // Combina las dos mitades ordenadas
    }
}
