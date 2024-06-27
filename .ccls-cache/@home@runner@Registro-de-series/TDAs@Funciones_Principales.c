//Librerías   ./Registro_de_series
// gcc TDAs/*.c Funciones_Principales.c main.c -o Registro_de_series

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "list.h"
#include "map.h"
#include "Priority_Queue.h"
#include "Funciones_Principales.h"

int is_equal_str(void *key1, void *key2) 
{
  return strcmp((char *)key1, (char *)key2) == 0;
}

//**************************************************************
//Funcion propia 1
void IngresarSerie(Map *ListaSeries)
{
  
  Serie *NuevaSerie;
  char Nombre[70]; 
  int Temporadas;
  int capitulos;
  int tiempo;

  
  // Se ingresan los valores de la nueva serie
  printf("Ingrese del nombre de la serie: \n");
  getchar();
  fgets(Nombre, sizeof(Nombre), stdin);
  Nombre[strcspn(Nombre, "\n")] = '\0';
  printf("Ingrese la cantidad de temporadas de la serie\n");
  scanf("%d", &Temporadas);
  printf("Ingrese la cantidad de capitulos por temporada:\n");
  scanf("%d", &capitulos);
  printf("Ingrese la duracion de cada capitulo en minutos:\n");
  scanf("%d", &tiempo);
  
  strcpy(NuevaSerie->Nombre, Nombre);
  NuevaSerie->Temporadas = list_create();
  NuevaSerie->Completada = false;
  NuevaSerie->Duracion = 0;
/*
  for(int i = 0; i < Temporadas; i++)
    {
      
      Temporada *Tempo = (Temporada*)malloc(sizeof(Temporada));
      if (Tempo == NULL) {
          printf("Error al asignar memoria para la temporada\n");
          return;
      }
      Tempo->Numero = i+1;
      Tempo->Capitulos = list_create();
      Tempo->Completada = false;
      
      for(int j = 0; j < capitulos; j++)
        {
          Capitulo *Cap = (Capitulo*)malloc(sizeof(Capitulo));
          Cap->Numero = j+1;
          Cap->Duracion = tiempo;
          Cap->Completado = false;
          list_pushBack(Tempo->Capitulos, Cap);
          Tempo->Duracion += tiempo;
        }
      list_insert(NuevaSerie.Temporadas, &Tempo->Numero, Tempo);
      
    }*/
  map_insert(ListaSeries, &NuevaSerie->Nombre, &NuevaSerie);
}

//**************************************************************
//Funcion propia 2
void IngresarEspecial(Map *ListaSeries)
{
  /*
  printf("Ingrese el nombre de la serie: ");
  char Nombre[70];
  fgets(Nombre, sizeof(Nombre), stdin);
  getchar();
  printf("Ingrese el numero de la temporada: ");
  int Tempo;
  scanf("%d", &Tempo);
  getchar();
  printf("Ingrese la duracion del especial");
  int tiempo;
  scanf("%d", &tiempo);
  getchar();

  MapPair *SerieTemp = map_search(ListaSeries, &Nombre);
  Serie *Aux = (Serie*)SerieTemp->value;
  Temporada *Temp = (Temporada*)map_search(Aux->Temporadas, &Tempo);
  Capitulo *Cap = list_first(Temp->Capitulos);
  while(Cap != NULL)
    {
      Cap = list_next(Temp->Capitulos);
    }
  Capitulo NewCap = {Cap->Numero+1, tiempo, false};
  list_pushBack(Temp->Capitulos, &NewCap);
  Temp->Duracion += tiempo;
  */
}

//*************************************************************
//Funcion propia 3
//en revision

void SeriesSinTerminar(Map *ListaSeries)
{
  /*
  int TiempoRestante=Series->Duracion;
  int TiempoTotal=0;
  int SeriesSinTerminar=0;
  int i=0;
  while(Series!=NULL)
    {
      
      if (Series->Completado==false))
        SeriesSinTerminar++;
      while(Series->Teporadas!=NULL)
        {
          i++; 
          TiempoRestante-=Series->Temporadas[i].Completadas.Duracion;
        }
      printf("Tiempo restante para terminar una serie=%d",TiempoRestante);
      
      TiempoTotal+=TiempoRestante;    
    }
  printf("Cantidad de series sin terminar=%d",SeriesSinTerminar); 

  printf("Cantidad de tiempo total para terminar todas las series=%d",TiempoTotal);
*/
}

//*************************************************************
//Funcion propia 4
//en revision

void AvanceSerie(Map *ListaSeries) 

{
  /*
  MapPair *Aux;

  char nombreSerie[70];
  printf("Ingrese el nombre de la serie: ");
  getchar();
  fgets(nombreSerie, sizeof(nombreSerie), stdin);
  nombreSerie[strcspn(nombreSerie, "\n")] = '\0';

  while (ListaSeries != NULL) {
    Aux = map_first(ListaSeries);
    Serie *serie = (Serie *)Aux->value;

    if (strcmp(serie->Nombre, nombreSerie) == 0) {
      int minutosVistos = 0;
      int minutosFaltantes = 0;

      printf("Avance de la serie: %s\n", serie->Nombre);

      Temporada *temporada = serie->Temporadas;

      while (temporada != NULL) {
        minutosVistos += temporada->Vistos;
        minutosFaltantes += temporada->Duracion - temporada->Vistos;

        temporada = temporada->next;
      }

      printf("Minutos vistos: %d\n", minutosVistos);
      printf("Minutos faltantes: %d\n", minutosFaltantes);

      return;
    }

    ListaSeries = ListaSeries->next;
  }

  printf("No se encontró la serie especificada.\n");
  */
}

void ActualizarSerie(Map *ListaSeries)
{
  
}

//*************************************************************
//Funcion propia 6
//en revision

void SeriesCompletas(Map *ListaSeries)
{
  /*
  int SeriesCompletadas=0;
  while(ListaSeries !=NULL)
    {
      if (Series->Completado==true)
        SeriesCompletadas++;

      printf("%c, Tiempo de la serie = %d minutos.",Series->Nombre, Series->Duracion);
    }
  printf("Cantidad de series completadas = %d minutos.",SeriesCompletadas);

  printf("Tiempo de las series completadas = %d minutos.",SeriesCompletadas*Series->Duracion); 
  */
}
