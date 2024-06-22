#include "ArregloExplicito.h"
#include "GapCoding.h"
#include "Huffman.h"
#include "Experimentacion.h"

using namespace std;

int main(int argc, char** argv){
    if (argc != 3){
        printf("Se debe ejecutar como './bin/prog n sttdv'\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int sstdv = atof(argv[2]);
    int media = 5;

    int* arregloLineal = creaArregloLineal(n);
    if (PRINT){
        cout << "Arreglo Lineal: ";
        imprimeArreglo(arregloLineal, n);
    }

    int* arregloNormal = creaArregloNormal(n, media, sstdv);
    if (PRINT){
        cout << "Arreglo Normal: ";         
        imprimeArreglo(arregloNormal, n);
    }
    int num;

    if (PRINT){
        do{
            cout << "Ingrese número: "<< endl;
            cin >> num;
            cout << "Indice del elemento: " << busquedaBinaria(arregloLineal, num, n) << endl;
        }while (num != -1);
    }
    
    // Gap Coding  
    int *arregloGCLineal = creaGC(arregloLineal, n);
    if (PRINT){
        cout << "Arreglo GC Lineal: ";         
        imprimeArreglo(arregloGCLineal, n);
    }

    int *arregloGCNormal = creaGC(arregloNormal, n);
    if (PRINT){
        cout << "Arreglo GC Normal: ";         
        imprimeArreglo(arregloGCNormal, n);
    }

    // Sample
    // calculamos m en funcion n, y b en funcion de m y n
    double logaritmo = log2(n);
    int m = static_cast<int>(ceil(logaritmo));
    int b = n/m;
    cout << "m: " << m << ", b: " << b << endl;

    int *arregloSampleLineal = creaSample(arregloLineal, n, m, b);
    if (PRINT){
        cout << "Arreglo Sample Lineal: ";         
        imprimeArreglo(arregloSampleLineal, m);
    }

    int *arregloSampleNormal = creaSample(arregloNormal, n, m, b);
    if (PRINT){
        cout << "Arreglo Sample Normal: ";         
        imprimeArreglo(arregloSampleNormal, m);
    }

    // Busqueda binaria con Gap Coding
    if (PRINT){
        do{
            cout << "Busqueda binaria GC del arreglo Lineal, Ingrese número: "<< endl;
            cin >> num;
            cout << "Indice del elemento: " << busquedaBinariaSample_GC(arregloGCLineal, arregloSampleLineal, num, n, m, b) << endl;
        }while (num != -1);
    }

    if (PRINT){
        do{
            cout << "Busqueda binaria GC del arreglo Normal, Ingrese número: "<< endl;
            cin >> num;
            cout << "Indice del elemento: " << busquedaBinariaSample_GC(arregloGCNormal, arregloSampleNormal, num, n, m, b) << endl;
        }while (num != -1);
    }

}