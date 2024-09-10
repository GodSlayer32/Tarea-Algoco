#include <iostream>
#include <fstream>
#include <random>

int main() {
    // Definir la cantidad de números a generar
    const int cantidadNumeros = 10;

    // Crear un generador de números aleatorios
    std::random_device rd;  // Fuente de entropía aleatoria
    std::mt19937 gen(rd()); // Motor de generación basado en Mersenne Twister
    std::uniform_int_distribution<> dis(1, 1000000000); // Rango de números aleatorios (ajusta según necesites)

    // Abrir el archivo de salida
    std::ofstream archivo("numeros4.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return 1;
    }

    // Generar y guardar los números aleatorios
    for (int i = 0; i < cantidadNumeros; ++i) {
        archivo << dis(gen) << "\n";
    }

    // Cerrar el archivo
    archivo.close();

    std::cout << "Se han generado y guardado " << cantidadNumeros << " números aleatorios en 'numeros4.txt'." << std::endl;
    return 0;
}
