//Librerías   ./Registro_de_series
// gcc TDAs/*.c Funciones_Principales.c main.c -o Registro_de_series

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "TDAs/list.h"
#include "TDAs/map.h"
#include "TDAs/Priority_Queue.h"
#include "Funciones_Principales.h"

//**************************************************************
//Funcion propia 1
void IngresarSerie(Map *Series)
{
  Serie NuevaSerie;
  printf("Ingrese el nombre de la serie: \n");
  char Nombre[70]; 
  fgets(Nombre, sizeof(Nombre), stdin);
  printf("Ingrese la cantidad de temporadas de la serie\n");
  int Temporadas;
  scanf("%d", &Temporadas);
  printf("Ingrese la cantidad de capitulos por temporada:\n");
  int capitulos;
  scanf("%d", &capitulos);
  printf("Ingrese la duracion de cada capitulo:\n");
  int tiempo;
  scanf("%d", &tiempo);

  NuevaSerie.Nombre = Nombre;
  NuevaSerie.Temporadas = map_create((void*)strcmp);
  NuevaSerie.Completada = false;

  for(int i = 0; i < Temporadas; i++)
    {
      Temporada *Tempo = (Temporada*)malloc(sizeof(Temporada));
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
      map_insert(NuevaSerie.Temporadas, &Tempo->Numero, Tempo);
    }
  map_insert(Series, &NuevaSerie.Nombre, &NuevaSerie);
  
}
//**************************************************************
//Funcion propia 2
void IngresarEspecial(Map *Series)
{
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

  MapPair *SerieTemp = map_search(Series, &Nombre);
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
}
//*************************************************************
//Funcion propia 3
//en revision

void SeriesSinTerminar(Map *Series)
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

  printf("Canitdad de tiempo total para terminar todas las series=%d",TiempoTotal);")
*/
}

//*************************************************************
//Funcion propia 4
//en revision

void AvanceSerie(Map *Series)
{
  /*
  int CapitulosCompletados=0;
  int TemporadasCompletadas=0;
  int i=0;
  int j=0;
  printf("Avance de la serie=%c",Series->Nombre);

  while(Series->Temporadas!=NULL)
    {
      i++;
      printf("Temporada=%d, visto=%d, faltantes=%d, duracion=%d", Series[i]->Temporadas.Numero, (Series[i]->Temporadas.Completada==true),(Series[i]->Temporadas.Completada==false), Series[i]->Temporadas.Duracion);

    while(Series->Temporadas->Capitulos!=NULL)
      {
        j++;
        Series->Temporadas.Duracion+=Series->Temporadas.Capitulos.Duracion);
        
        //determinar si una serie esta completa
        if(Serie->Temporadas->Capitulos->Completado==true))
        {
          CapitulosCompletados++;
          if(CapitulosCompletados==j)
          {
            (Serie->Temporadas->Completado==true);
            TemporadasCompletadas++;
            if (TemporadasCompletadas == i)
              (Serie->Completado==true);
  
          }
        }
      }
    }
    */
}

 
//*************************************************************
//Funcion propia 5
//en revision

void ActualizarSerie(Map *Series)
{ 
  /*
  //se accede a una serie y actualizar el tiempo visto y los capitulos completados
  while(Series->Temporadas!=NULL)
    {
      Serie->Temporada.Capitulo[i].Completado==false;

      while(Serie->Temporada.Capitulo!=NULL && Serie->TiempoVisto>0)
        {
          if(Serie->Temporada.Capitulo[i].Duracion>=Serie->TiempoVisto)
          {
            Serie->Temporada.Capitulo[i].Completado==true;
          }
          Serie->Temporada.Capitulo[i]=Serie->Temporada.Capitulo[i+1]
        }
      Serie->Temporada[i]=Serie->Temporada[i+1];

    }  
    */
}

//*************************************************************
//Funcion propia 6
//en revision

void SeriesCompletas(Map *Series)
{
  /*
  int SeriesCompletadas=0;
  while(Series!=NULL)
    {
      if (Series->Completado==true)
        SeriesCompletadas++;

      printf("Tiempo de la serie=%d", Serie->Duracion);
    }
  printf("Cantidad de series completadas=%d",SeriesCompletadas);

  printf("Tiempo de las series completadas=%d",SeriesCompletadas*Series->Duracion);
  */
}
