#include "Experimentacion.h"

using namespace std;

//Toma una marca de la Ram que está utilizando el programa en un momento x
void experimentacion::tomaMarcaIniRam(){
    getrusage(RUSAGE_SELF, &(this->resource_usage));
    this->ini_RAM = resource_usage.ru_maxrss;
}

//Toma una marca de la Ram que se está utilizando en un momento x. Resta con la inicial y imprime en MegaBytes
void experimentacion::imprimeRamUsada (){
    getrusage(RUSAGE_SELF, &(this->resource_usage));
    this->fin_RAM = resource_usage.ru_maxrss;
    printf("Memoria utilizada por la ED: %0.3fMB\n", fin_RAM-ini_RAM/1e3);
}

//Toma una marca del tiempo en un momento x
void experimentacion::tomaIniTiempo(){
    this->ini_tiempo = chrono::high_resolution_clock::now();
}

//Toma una marca del tiempo en un momento x. Compara con el inicial e imprime en nanosegundos
void experimentacion::imprimeTiempo(){
    this->fin_tiempo = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(fin_tiempo - ini_tiempo);
    printf("Buscar en la estructura %0.e veces en promedio llevó un tiempo medio de: %0.f nanosegundos\n\n",  REP, (double)elapsed_time.count()/REP); //Se imprime el tiempo que llevó
}