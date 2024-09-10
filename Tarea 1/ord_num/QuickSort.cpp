#include <iostream>  // Para operaciones de entrada y salida
#include <fstream>   // Para la manipulación de archivos
#include <vector>    // Para el uso de vectores dinámicos
#include <chrono>    // Para medir tiempos de ejecución
#include <algorithm> // Para std::sort

using namespace std;

// Función para intercambiar dos elementos en un vector.
// Parámetros:
// - a: Referencia al primer entero que se desea intercambiar.
// - b: Referencia al segundo entero que se desea intercambiar.
void intercambiar(int& a, int& b) {
    int temp = a;  // Variable temporal para almacenar el valor de 'a'
    a = b;         // Asigna a 'a' el valor de 'b'
    b = temp;      // Asigna a 'b' el valor almacenado en 'temp' (valor original de 'a')
}

// Función para encontrar la posición de partición del vector usando el último elemento como pivote.
// Parámetros:
// - arr: Referencia al vector de enteros que contiene los elementos a ordenar.
// - bajo: Índice del inicio del subarreglo.
// - alto: Índice del final del subarreglo.
// Retorna el índice de la nueva posición del pivote.
int particion(std::vector<int>& arr, int bajo, int alto) {
    int pivote = arr[alto]; // Tomar el último elemento como pivote
    int i = bajo - 1;      // Índice del elemento más pequeño

    // Recorre el subarreglo y coloca los elementos menores que el pivote a la izquierda
    for (int j = bajo; j <= alto - 1; ++j) {
        if (arr[j] < pivote) {
            ++i;              // Incrementa el índice del elemento más pequeño
            intercambiar(arr[i], arr[j]); // Intercambia los elementos
        }
    }

    // Coloca el pivote en su posición correcta
    intercambiar(arr[i + 1], arr[alto]);
    return (i + 1); // Retorna la posición del pivote
}

// Función principal de Quick Sort que ordena el vector de manera recursiva.
// Parámetros:
// - arr: Referencia al vector de enteros que se desea ordenar.
// - bajo: Índice del inicio del subarreglo.
// - alto: Índice del final del subarreglo.
void quickSort(std::vector<int>& arr, int bajo, int alto) {
    if (bajo < alto) {  // Si el subarreglo tiene más de un elemento
        int pi = particion(arr, bajo, alto); // Encuentra la posición de partición

        // Ordena recursivamente los subarreglos antes y después de la partición
        quickSort(arr, bajo, pi - 1);  // Ordena el subarreglo izquierdo
        quickSort(arr, pi + 1, alto); // Ordena el subarreglo derecho
    }
}
