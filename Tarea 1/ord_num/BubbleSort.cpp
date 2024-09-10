#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
// Función para realizar Bubble Sort en un arreglo.
// Este algoritmo de ordenamiento es simple pero no es eficiente para grandes conjuntos de datos
// debido a su complejidad temporal de O(n^2), lo que lo hace lento para grandes tamaños.

// Parámetros:
// - arr: referencia a un vector de enteros que se desea ordenar en orden ascendente.

// Descripción:
// La función `bubbleSort` ordena un vector de enteros utilizando el algoritmo de Bubble Sort.
// Este algoritmo funciona comparando de manera repetida elementos adyacentes del vector
// y los intercambia si están en el orden incorrecto, "burbujeando" los valores más grandes
// hacia el final del vector con cada iteración completa a través del vector.
// Función para realizar Bubble Sort en el arreglo (no recomendada para grandes tamaños)

void bubbleSort(vector<int>& arr) {
    int n = arr.size(); //Obtiene el tamaño del vector
    //Bucle exterior: recorre desde el primer elemento hasta el penultimo
    for (int i = 0; i < n - 1; ++i) {
        //Bucle interior: Recorre desde el primer elemento hasta el elemento n-i-1
        //Cada iteración del bulcle exterior, el rango del bucle exterior se reduce
        //porque el ultimo elemento de la iteración anterior ya está en su posición correcta
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Intercambiar los elementos si el elemento actuale es mayor al siguiente
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}