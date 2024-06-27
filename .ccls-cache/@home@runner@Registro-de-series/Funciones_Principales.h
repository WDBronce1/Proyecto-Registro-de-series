#ifndef FUNCIONES_PRINCIPALES_H
#define FUNCIONES_PRINCIPALES_H

// Incluir las librerías necesarias
#include <stdbool.h>
#include "TDAs/list.h"
#include "TDAs/map.h"
#include "TDAs/Priority_Queue.h"

// Estructuras
typedef struct {
    char *Nombre;
    Map *Temporadas;
    int Duracion;
    bool Completada;
    int TiempoVisto;
} Serie;

typedef struct {
    int Numero;
    List *Capitulos;
    int Duracion;
    bool Completada;
} Temporada;

typedef struct {
    int Numero;
    int Duracion;
    bool Completado;
} Capitulo;

// Declaraciones de las funciones
void IngresarSerie(Map *Series);
void IngresarEspecial(Map *Series);
void SeriesSinTerminar(Map *Series);
void AvanceSerie(Map *Series);
void ActualizarSerie(Map *Series);
void SeriesCompletas(Map *Series);

#endif // FUNCIONES_PRINCIPALES_H
