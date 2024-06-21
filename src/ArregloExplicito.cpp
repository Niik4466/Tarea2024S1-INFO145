#include "ArregloExplicito.h"
using namespace std;

// Crea un arreglo ordenado siguiendo la distribución lineal
int* creaArregloLineal(int largo){
    int* arr = new int[largo];
    arr[0] = rand() % EPSILON;
    for(int i = 1; i < largo; i++){
        arr[i] = arr[i-1] + rand()%(EPSILON+1);
    }
    return arr;
}

// Crea un arreglo ordenado siguiendo la distribución normal
int* creaArregloNormal(int largo, double media, double desviacionEstandar){
    random_device rd;  // Generador de números aleatorios no determinista
    mt19937 gen(rd()); // Generador Mersenne Twister
    normal_distribution<double> d(media, desviacionEstandar);

    int* arr = new int[largo];
    
    for (int i = 0; i < largo; ++i) {
        arr[i] = d(gen);
    }

    // Ordenar el arreglo de menor a mayor
    sort(arr, arr + largo);
    return arr;
    
    return nullptr;
}

/*
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <limits.h>

using namespace std;

// Función para generar un arreglo de números aleatorios con distribución normal
vector<int> generarArregloNormal(int tamano, double media, double desviacionEstandar) {
    // Motor de números aleatorios y distribución normal
    random_device rd;
    mt19937 generador(rd());
    normal_distribution<double> distribucion(media, desviacionEstandar);

    // Vector para almacenar los números generados
    vector<int> arreglo(tamano);

    // Generar números aleatorios y almacenarlos en el vector
    for (int i = 0; i < tamano; ++i) {
        arreglo[i] = distribucion(generador);
    }

    // Ordenar el arreglo de menor a mayor
    sort(arreglo.begin(), arreglo.end());

    return arreglo;
}

int main() {
    // Parámetros para la generación del arreglo
    int tamano = 1e3; // Tamaño del arreglo
    double media = INT_MAX/2; // Media de la distribución normal
    double desviacionEstandar = 1.5; // Desviación estándar de la distribución normal

    // Generar el arreglo
    vector<int> arreglo = generarArregloNormal(tamano, media, desviacionEstandar);

    // Imprimir el arreglo ordenado
    cout << "Arreglo ordenado con distribución normal:" << endl;
    for (double valor : arreglo) {
        cout << valor << " ";
    }
    cout << endl;

    return 0;
}
*/









int busqueda_binaria(int* arreglo,int x, int n) {
    int izq = 0, der = n - 1, l = 0;
    while (izq <= der) {
        int medio = izq + (der - l) / 2;
        if (arreglo[medio] == x)
            return medio;
        if (arreglo[medio] < x)
            izq = medio + 1;
        else
            der = medio - 1;
    }
    return -1;
}

void imprimeArreglo(int* arreglo, int largo){
    for(int i = 0; i < largo; i++){
        cout << arreglo[i] << " ";
    }
    cout << endl;
}