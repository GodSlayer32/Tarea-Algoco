#include <iostream>
#include <fstream>
#include <random>

int main() {
    // Definir la cantidad de números a generar
    const int cantidadNumeros = 10;

    // Abrir el archivo de salida
    std::ofstream archivo("numeros.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return 1;
    }

    // Generar y guardar los números aleatorios
    for (int i = 0; i < cantidadNumeros; ++i) {
        archivo << i << "\n"; //genera los numeros ordenados ascendentemente
        //archivo<< cantidadNumeros-i<<"\n"; //genera los numeros ordenados descendentemente
    }

    // Cerrar el archivo
    archivo.close();

    std::cout << "Se han generado y guardado " << cantidadNumeros << " números aleatorios en 'numeros1.txt'." << std::endl;
    return 0;
}