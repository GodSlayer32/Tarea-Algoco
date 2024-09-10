#include <iostream>  // Para operaciones de entrada y salida
#include <fstream>   // Para la manipulación de archivos
#include <vector>    // Para el uso de vectores dinámicos
#include <chrono>    // Para medir tiempos de ejecución
#include <algorithm> // Para std::sort

using namespace std;

const int TAMANO = 10; // Tamaño del arreglo

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
int particion(vector<int>& arr, int bajo, int alto) {
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
void quickSort(vector<int>& arr, int bajo, int alto) {
    if (bajo < alto) {  // Si el subarreglo tiene más de un elemento
        int pi = particion(arr, bajo, alto); // Encuentra la posición de partición

        // Ordena recursivamente los subarreglos antes y después de la partición
        quickSort(arr, bajo, pi - 1);  // Ordena el subarreglo izquierdo
        quickSort(arr, pi + 1, alto); // Ordena el subarreglo derecho
    }
}

//#######################################################################################################################################
// Función para realizar Bubble Sort en el arreglo (no recomendada para grandes tamaños)
// Parámetros:
// - arr: Referencia al vector de enteros que se desea ordenar.
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Intercambiar los elementos si están en el orden incorrecto
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
//#######################################################################################################################################

// Función para fusionar dos mitades ordenadas del vector en una sola secuencia ordenada.
// Parámetros:
// - arr: Referencia al vector de enteros que contiene los elementos a ordenar.
// - izquierda: Índice de inicio de la primera mitad del vector.
// - medio: Índice que separa las dos mitades; final de la primera mitad.
// - derecha: Índice de fin de la segunda mitad del vector.
void merge(vector<int>& arr, int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1; // Tamaño del subvector izquierdo
    int n2 = derecha - medio;       // Tamaño del subvector derecho

    // Crear subarreglos temporales
    vector<int> L(n1);
    vector<int> R(n2);

    // Copiar datos a los subarreglos
    for (int i = 0; i < n1; ++i)
        L[i] = arr[izquierda + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[medio + 1 + j];

    // Fusionar los subarreglos en arr[]
    int i = 0; // Índice inicial del primer subarreglo
    int j = 0; // Índice inicial del segundo subarreglo
    int k = izquierda; // Índice inicial del subarreglo fusionado

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Función principal de Merge Sort que ordena el vector de manera recursiva.
// Parámetros:
// - arr: Referencia al vector de enteros que se desea ordenar.
// - izquierda: Índice de inicio del subvector a ordenar.
// - derecha: Índice de fin del subvector a ordenar.
void mergeSort(vector<int>& arr, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2; // Calcula el índice del medio

        // Ordenar la primera y la segunda mitad
        mergeSort(arr, izquierda, medio);
        mergeSort(arr, medio + 1, derecha);

        // Fusionar las dos mitades ordenadas
        merge(arr, izquierda, medio, derecha);
    }
}
//#######################################################################################################################################

int main() {
    // Nombres de los archivos de entrada y salida
    vector<string> archivosEntrada = {
        "/home/godslayerdev/Algoco/Tarea 1/generadores/numeros.txt",
        "/home/godslayerdev/Algoco/Tarea 1/generadores/numeros2.txt",
        "/home/godslayerdev/Algoco/Tarea 1/generadores/numeros3.txt",
        "/home/godslayerdev/Algoco/Tarea 1/generadores/numeros4.txt"
    };

    vector<string> archivosSalida = {
        "resultados1.txt",
        "resultados2.txt",
        "resultados3.txt",
        "resultados4.txt"
    };

    for (size_t i = 0; i < archivosEntrada.size(); ++i) {
        vector<int> arreglo(TAMANO); // Crear un vector de enteros con tamaño TAMANO
        ifstream archivoEntrada(archivosEntrada[i]); // Abrir el archivo de entrada

        if (!archivoEntrada) {
            cerr << "Error al abrir el archivo de entrada: " << archivosEntrada[i] << endl;
            return 1;
        }

        // Leer los números del archivo y almacenarlos en el vector
        for (int j = 0; j < TAMANO; ++j) {
            archivoEntrada >> arreglo[j];
            if (archivoEntrada.fail()) {
                cerr << "Error al leer el número en la posición " << j << " del archivo " << archivosEntrada[i] << "." << endl;
                return 1;
            }
        }

        archivoEntrada.close();

        // Medir el tiempo de ejecución de la función de ordenamiento
        auto inicio = chrono::high_resolution_clock::now(); // Momento de inicio

        // Puedes usar bubbleSort si realmente necesitas, pero es muy lento para grandes tamaños
        //bubbleSort(arreglo);  // Ordena usando Bubble Sort
        //mergeSort(arreglo, 0, TAMANO - 1); // Ordena usando Merge Sort
        //quickSort(arreglo, 0, TAMANO - 1); // Ordena usando Quick Sort
        sort(arreglo.begin(), arreglo.end()); // Ordena usando std::sort

        auto fin = chrono::high_resolution_clock::now();    // Momento de finalización

        // Calcular la duración en segundos
        chrono::duration<double> duracion = fin - inicio;
        cout << "El tiempo de ejecución de ordenamiento para " << "numeros " << i << " fue: " << duracion.count() << " s" << endl;

        // Guardar los números ordenados en el archivo de salida correspondiente
        ofstream archivoSalida(archivosSalida[i]);
        if (!archivoSalida) {
            cerr << "Error al abrir el archivo de salida: " << archivosSalida[i] << endl;
            return 1;
        }

        for (int j = 0; j < TAMANO; ++j) {
            archivoSalida << arreglo[j] << "\n";
        }

        archivoSalida.close();

        cout << "Los números del archivo " << "numeros " << i + 1  << " han sido ordenados y guardados en " << archivosSalida[i] << "." << endl;
    }

    return 0;
}
