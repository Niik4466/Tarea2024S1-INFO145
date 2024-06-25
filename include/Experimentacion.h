#ifndef Experimentacion_H
#define Experimentacion_H

#include <chrono>           //Utilizado para medir el tiempo que se demora en realizar las búsquedas https://cplusplus.com/reference/chrono/
#include <sys/resource.h>   //Utilizado para medir la memoria RAM utilizada en ejecución https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysresource.h.html
#include <cstdio>

#define PRINT 0
#define REP 1e4
#define EXP 0

// Definicion de la clase

class experimentacion{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> ini_tiempo;
    std::chrono::time_point<std::chrono::high_resolution_clock> fin_tiempo;
    float ini_RAM;
    float fin_RAM;
    struct rusage resource_usage;
public:
    experimentacion(){
        this->ini_RAM = 0.0;
        this->fin_RAM = 0.0;
    }

    //Métodos
    void tomaMarcaIniRam(); //Toma una marca de la Ram que está utilizando el programa en un momento x
    void imprimeRamUsada(); //Toma una marca de la Ram que se está utilizando en un momento x. Resta con la inicial y imprime en MegaBytes
    void tomaIniTiempo();   //Toma una marca del tiempo en un momento x
    void imprimeTiempo();   //Toma una marca del tiempo en un momento x. Compara con el inicial e imprime en nanosegundos
};

#endif