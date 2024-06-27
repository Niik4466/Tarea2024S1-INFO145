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

    int n = atoi(argv[1]); // Tamaño del arreglo
    if (n < 2){
        printf("n debe ser mayor a 1\n");
        exit(EXIT_FAILURE);
    }
    int sd = atof(argv[2]); // Desviación estandar
    int media = 1e8;

    /*if(EXP)
        experimentacion exp;

    if (EXP)
        exp.tomaMarcaIniRam();
    */
    int* arregloLineal = creaArregloLineal(n);
    
    /*if (EXP)
        exp.imprimeRamUsada();*/

    if (PRINT == 0){
        cout << "Arreglo Lineal: ";
        imprimeArreglo(arregloLineal, n);
    }

    int* arregloNormal = creaArregloNormal(n, media, sd);
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

    cout << "sample, " << endl;
    // Sample
    // calculamos m en funcion n, y b en funcion de m y n
    double logaritmo = log2(n);
    int m = static_cast<int>(ceil(logaritmo));
    int b = n/m;
    //cout << "m: " << m << ", b: " << b << endl;

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
    
    // Frecuencia de los arreglos GC
    cout <<"frecuencia, no mori" << endl;
    vector<simboloFrec> frecuenciaGCLineal = frecuenciaGC(arregloGCLineal, n);
    if (PRINT == 0){
        cout << "Frecuencia de los arreglos GC Lineal: " << endl;
        imprimeFrecuencia(frecuenciaGCLineal);
    }
    vector<simboloFrec> frecuenciaGCNormal = frecuenciaGC(arregloGCNormal, n);
    if (PRINT == 0){
        cout << "Frecuencia de los arreglos GC Normal: " << endl;
        imprimeFrecuencia(frecuenciaGCNormal);
    }
    cout << "post frecuencia" << endl;
    /*
    // Codificacion Huffman
    vector<simboloCod> simboloCodLineal = crearCodificacionHuffman(frecuenciaGCLineal);
    if (PRINT == 0){
        cout << "SimboloCodLineal\n";
        for (int i = 0; i < simboloCodLineal.size(); ++i){
            cout << "\nSimbolo " << simboloCodLineal[i].simbolo << ", frecuencia " << frecuenciaGCLineal[i].frecuencia << endl;
            cout << "Codificacion: ";
            for (int j = 0; j < simboloCodLineal[i].codification.size(); j++){
                cout << simboloCodLineal[i].codification[j] << " ";
            }
        }
        cout << endl;
    }
    
    vector<simboloCod> simboloCodNormal = crearCodificacionHuffman(frecuenciaGCNormal);
    if (PRINT == 0){
        cout << "SimboloCodNormal\n";
        for (int i = 0; i < simboloCodNormal.size(); ++i){
            cout << "\n Simbolo " << simboloCodNormal[i].simbolo << ", frecuencia " << frecuenciaGCNormal[i].frecuencia << endl;
            cout << "Codificacion: ";
            for (int j = 0; j < simboloCodNormal[i].codification.size(); j++){
                cout << simboloCodNormal[i].codification[j] << " ";
            }
        }
        cout << endl;
    }
    */
    /*
    // traduciendo a char
    cout << "SimboloCodCharLineal\n";
    vector<simboloCodChar> simboloCodCharLineal = traducir(simboloCodLineal);
    for (int i = 0; i < simboloCodCharLineal.size(); ++i){
        printf("\nSimbolo %i", simboloCodCharLineal[i].simbolo);
        cout << "\nRepresentacion: " << simboloCodCharLineal[i].representacion;
        cout <<"\nnumero: " << static_cast<int>(simboloCodCharLineal[i].representacion);
    }
    cout << endl;
    cout << "SimboloCodCharNormal\n";
    vector<simboloCodChar> simboloCodCharNormal = traducir(simboloCodNormal);
    for (int i = 0; i < simboloCodCharNormal.size(); ++i){
        printf("\nSimbolo %i", simboloCodCharNormal[i].simbolo);
        cout << "\nRepresentacion: " << simboloCodCharNormal[i].representacion;
        cout <<"\nnumero: " << static_cast<int>(simboloCodCharNormal[i].representacion);
    }
    */
    // Decodificacion 
/*
    unordered_map<unsigned char, int> decodificar = CreateHash(simboloCodCharLineal);

    */

}