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

    //------------------VALORES PARA INICIALIZAR EL PROGRAMA----------------------------
    int n = atoi(argv[1]); // Tamaño del arreglo
    if (n < 2){
        printf("n debe ser mayor a 1\n");
        exit(EXIT_FAILURE);
    }
    int sd = atof(argv[2]); // Desviación estandar
    int media = 1e8;


    Experimentacion exp; // creamos un objeto de nuestra clase experimentación definida en experimentacion.h

    //------------------------ EXPERIMENTACION RAM ARREGLO LINEAL ----------------------------
    if(EXP){
        printf("Uso de Ram del arreglo con dist Lineal\n");
        exp.tomaMarcaIniRam();
    }
    int* arregloLineal = creaArregloLineal(n);
    if(EXP){
        exp.imprimeRamUsada();
    }

    //imrpimimos el arreglo lineal si PRINT = 1
    if (PRINT){
        cout << "Arreglo Lineal: ";         
        imprimeArreglo(arregloLineal, n);
    }


    //------------------------- EXPERIMENTACION RAM ARRELGO NORMAL ---------------------------
    if(EXP){
        printf("Uso de Ram del arreglo con dist Normal\n");
        exp.tomaMarcaIniRam();
    }
    int* arregloNormal = creaArregloNormal(n, media, sd);
    
    if(EXP){
        exp.imprimeRamUsada();
    }
    
    // imprimimos el arreglo 
    if (PRINT){
        cout << "Arreglo Normal: ";         
        imprimeArreglo(arregloNormal, n);
    }

    
    //---------------------- EXPERIMENTACION CREAR GAP CODING LINEAL-----------------
    if(EXP){
        printf("Uso de Ram del arreglo GAP CodingLineal\n");
        exp.tomaMarcaIniRam();
    }
    int *arregloGCLineal = creaGC(arregloLineal, n);
    if(EXP){
        exp.imprimeRamUsada();
    }
    
    //--------------------- EXPERIMENTACION CREAR GAP CODING NORMAL-------------------------------
    if(EXP){
        printf("Uso de Ram del arreglo GAP CodingNormal\n");
        exp.tomaMarcaIniRam();
    }
    int *arregloGCNormal = creaGC(arregloNormal, n);
    if(EXP){
        exp.imprimeRamUsada();
    }
    
    // --------------------------CREAR SAMPLE---------------------------
    double logaritmo = log2(n);
    int m = static_cast<int>(ceil(logaritmo));
    int b = n/m;
    int *arregloSampleLineal = creaSample(arregloLineal, n, m, b);
    int *arregloSampleNormal = creaSample(arregloNormal, n, m, b);

    // -----------------------Frecuencia de los arreglos GC-------------------------
    vector<simboloFrec> frecuenciaGCLineal = frecuenciaGC(arregloGCLineal, n);
    vector<simboloFrec> frecuenciaGCNormal = frecuenciaGC(arregloGCNormal, n);

    //-------------------------CREAR CODIFICACION HUFFMAN-----------------
    vector<simboloCod> simboloCodLineal = crearCodificacionHuffman(frecuenciaGCLineal);
    if (PRINT){
        cout << "\nSimboloCodLineal\n";
        for (int i = 0; i < simboloCodLineal.size(); ++i){
            cout << "\nSimbolo " << simboloCodLineal[i].simbolo << ", frecuencia " << frecuenciaGCLineal[i].frecuencia << endl;
            cout << "Codificacion: ";
            for (int j = 0; j < simboloCodLineal[i].codification.size(); j++){
                cout << simboloCodLineal[i].codification[j] << " ";
            }
        cout << endl;
        }
    }
    
    vector<simboloCod> simboloCodNormal = crearCodificacionHuffman(frecuenciaGCNormal);
    if (PRINT){
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

    // -------------------Traduccion de simboloCod a simboloCodChar--------------------------
    vector<simboloCodChar> simboloCodCharLineal = traducir(simboloCodLineal);
    vector<simboloCodChar> simboloCodCharNormal = traducir(simboloCodNormal);

    // -------------------------------Decodificacion-------------------------------------- 
    unordered_map<unsigned char, int> decodificacionLineal = CreateHash(simboloCodCharLineal);
    unordered_map<unsigned char, int> decodificacionNormal = CreateHash(simboloCodCharNormal);
    
    // --------------------------EXPERIMENTACION GC LINEAL CODIFICADO A HUFFMAN-----------------
    if(EXP){
        printf("Uso de Ram de transformar arreglo GC lineal a GC codficado por Huffman\n");
        exp.tomaMarcaIniRam();
    }
    unsigned char* arregloGCHuffmanLineal = transformarGCaGCHuffman(arregloGCLineal, simboloCodCharLineal, n);
    if(EXP){
        exp.imprimeRamUsada();
    }
    
    // --------------------------EXPERIMENTACION GC NORMAL CODIFICADO A HUFFMAN-----------------
    if(EXP){
        printf("Uso de Ram de transformar arreglo GC normal a GC codificado por Huffman\n");
        exp.tomaMarcaIniRam();
    }
    unsigned char* arregloGCHuffmanNormal = transformarGCaGCHuffman(arregloGCNormal, simboloCodCharNormal, n);
    if(EXP){
        exp.imprimeRamUsada();
    }
    
    //IMPRIMIR GC LINEAL 
    if (PRINT){
        cout << "GC Lineal: ";         
        imprimeArreglo(arregloGCLineal, n);
    }

    //--------------------------- BUSQUEDA BINARIA MANUAL CON GAP CODING CODIFICADO -------------------- 
    int num;
    if (PRINT){

        do{
            cout << "Busqueda binaria GC Codificado del arreglo Lineal, Ingrese número: "<< endl;
            cin >> num;
            cout << "Indice del elemento: " << busquedaBinariaSample_GCHuffman(arregloGCHuffmanLineal, arregloSampleLineal, num, n, m, b, decodificacionLineal) << endl;
        }while (num != -1);
    }

    if (PRINT){
        do{
            cout << "Busqueda binaria GC Codificado del arreglo Normal, Ingrese número: "<< endl;
            cin >> num;
            cout << "Indice del elemento: " << busquedaBinariaSample_GCHuffman(arregloGCHuffmanNormal, arregloSampleNormal, num, n, m, b, decodificacionNormal) << endl;
        }while (num != -1);
    }

    //------------------------ EXPERIMENTACIÓN DE TIEMPOS DE BÚSQUEDA ----------------------------------------
    //int num;
    // ----------------------- EXPERIMENTACIÓN PARA EL ARREGLO CON DIST LINEAL ----------------------------------------

    printf("Experimentación de búsqueda para el Arreglo con dist Lineal\n");
    exp.tomaIniTiempo();
    for (int i = 0; i < REP; ++i){
        num = arregloLineal[0] + rand() % (arregloLineal[n-1] - arregloLineal[0] + 1);
        busquedaBinaria(arregloLineal, num, n);
    }
    exp.imprimeTiempo();

    // ----------------------- EXPERIMENTACIÓN PARA EL ARREGLO CON DIST NORMAL ----------------------------------------
    printf("Experimentación de búsqueda para el Arreglo con dist Normal\n");
    exp.tomaIniTiempo();
    for (int i = 0; i < REP; ++i){
        num = arregloNormal[0] + rand() % (arregloNormal[n-1] - arregloNormal[0] + 1);
        busquedaBinaria(arregloNormal, num, n);
    }
    exp.imprimeTiempo();

    // ----------------------- EXPERIMENTACIÓN PARA EL GAP CODING CON DIST LINEAL ----------------------------------------
    printf("Experimentación de búsqueda para el Gap Coding con dist Lineal\n");
    exp.tomaIniTiempo();
    for (int i = 0; i < REP; ++i){
        num = arregloLineal[0] + rand() % (arregloLineal[n-1] - arregloLineal[0] + 1);
        busquedaBinariaSample_GC(arregloGCLineal, arregloSampleLineal, num, n, m, b);
    }
    exp.imprimeTiempo();    
    

    // ----------------------- EXPERIMENTACIÓN PARA EL GAP CODING CON DIST NORMAL ----------------------------------------
    printf("Experimentación de búsqueda para el Gap Coding con dist Normal\n");
    exp.tomaIniTiempo();
    for (int i = 0; i < REP; ++i){
        num = arregloNormal[0] + rand() % (arregloNormal[n-1] - arregloNormal[0] + 1) ;
        busquedaBinariaSample_GC(arregloGCNormal, arregloSampleNormal, num, n, m, b);
    }
    exp.imprimeTiempo();

    // ----------------------- EXPERIMENTACIÓN PARA EL GAP CODING CODIFICADO CON DIST LINEAL ----------------------------------------
    printf("Experimentación de búsqueda para el Gap Coding Codificado con dist Lineal\n");
    exp.tomaIniTiempo();
    for (int i = 0; i < REP; ++i){
        num = arregloLineal[0] + rand() % (arregloLineal[n-1] - arregloLineal[0] + 1) ;
        busquedaBinariaSample_GCHuffman(arregloGCHuffmanLineal, arregloSampleLineal, num, n, m, b, decodificacionLineal);
    }
    exp.imprimeTiempo();

    // ----------------------- EXPERIMENTACIÓN PARA EL GAP CODING CODIFICADO CON DIST NORMAL ----------------------------------------
    printf("Experimentación de búsqueda para el Gap Coding Codificado con dist Normal\n");    
    exp.tomaIniTiempo();
    for (int i = 0; i < REP; ++i){
        num = arregloNormal[0] + rand() % (arregloNormal[n-1] - arregloNormal[0] + 1);
        busquedaBinariaSample_GCHuffman(arregloGCHuffmanNormal, arregloSampleNormal, num, n, m, b, decodificacionNormal);
    }
    exp.imprimeTiempo();

    return(EXIT_SUCCESS);
}