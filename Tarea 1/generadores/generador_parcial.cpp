#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

// Función para generar un archivo con números parcialmente ordenados
void generarNumerosParcialmenteOrdenados(const std::string& nombreArchivo, int totalNumeros, double porcentajeOrdenado) {
    std::vector<int> numeros(totalNumeros);
    
    // Generar números ordenados del 1 al totalNumeros
    for (int i = 0; i < totalNumeros; ++i) {
        numeros[i] = i + 1;
    }
    
    // Calcular cuántos números van a estar ordenados
    int cantidadOrdenada = static_cast<int>(totalNumeros * porcentajeOrdenado);
    
    // Mezclar los números no ordenados
    if (cantidadOrdenada < totalNumeros) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(numeros.begin() + cantidadOrdenada, numeros.end(), std::default_random_engine(seed));
    }

    // Escribir los números en un archivo
    std::ofstream archivoSalida(nombreArchivo);
    if (archivoSalida.is_open()) {
        for (int numero : numeros) {
            archivoSalida << numero << "\n";
        }
        archivoSalida.close();
        std::cout << "Archivo generado exitosamente: " << nombreArchivo << std::endl;
    } else {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
    }
}

int main() {
    std::string nombreArchivo = "numeros3.txt";
    int totalNumeros;
    double porcentajeOrdenado;

    // Pedir al usuario los parámetros
    std::cout << "Ingrese el número total de números a generar: ";
    std::cin >> totalNumeros;
    
    std::cout << "Ingrese el porcentaje de números que deben estar ordenados (entre 0.0 y 1.0): ";
    std::cin >> porcentajeOrdenado;
    
    // Generar el archivo con los números parcialmente ordenados
    generarNumerosParcialmenteOrdenados(nombreArchivo, totalNumeros, porcentajeOrdenado);

    return 0;
}
