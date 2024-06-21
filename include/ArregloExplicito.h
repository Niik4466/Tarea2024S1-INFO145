#ifndef ArregloExplicito_H
#define ArregloExplicito_H

#include <iostream>
#include <cstdlib>
#include <random>

#include <algorithm>

#define EPSILON 10

int* creaArregloLineal(int largo);
int busqueda_binaria(int* arreglo,int x, int n);
int* creaArregloNormal(int largo, double media, double desviacionEstandar);
void imprimeArreglo(int* arreglo, int largo);

#endif