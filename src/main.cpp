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
    sstdv = atof(argv[2]);
    media = 5;

    int* arregloLineal = creaArregloLineal(n);
    imprimeArreglo(arregloLineal, n);

    //int* arregloGap = creaGap(arregloLineal, n);
    //imprimeArreglo(arregloGap, n);

    int* arregloNormal = creaArregloNormal(n, media, sstdv);
    imprimeArreglo(arregloNormal, n);


   //int *GapCoding = creaGap(arr);

}