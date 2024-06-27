// gcc TDAs/*.c Funciones_Principales.c main.c -o Registro_de_series

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "TDAs/extra.h"
#include "TDAs/list.h"
#include "TDAs/map.h"
#include "TDAs/Priority_Queue.h"


// Estructuras
typedef struct {
    char *Nombre;
    List *Temporadas;
    int Duracion;
    bool Completada;
    int TiempoVisto;
} Serie;

typedef struct {
    int Numero;
    List *Capitulos;
    int Duracion;
    bool Completada;
    int TiempoVisto;
} Temporada;

typedef struct {
    int Numero;
    int Duracion;
    bool Completado;
} Capitulo;


// FUNCIONES AUXILIARES *********************************************
int is_equal_str(void *key1, void *key2) 
{
  return strcmp((char *)key1, (char *)key2) == 0;
}

void EnterContinuar()
{
    printf("Presione Enter para continuar...");
    getchar(); // Espera a que el usuario presione Enter
    getchar(); // Consumo del Enter que se presionó
}
//********************************************************************

void IngresarSerie(Map *ListaSeries)
{
    // Asignar memoria para la nueva serie
    Serie *NuevaSerie = (Serie*)malloc(sizeof(Serie));
    if (NuevaSerie == NULL) 
    {
        printf("Error al asignar memoria para la nueva serie\n");
        return;
    }

    // Asignar memoria para el nombre de la serie
    NuevaSerie->Nombre = (char*)malloc(70 * sizeof(char));
    if (NuevaSerie->Nombre == NULL) 
    {
        printf("Error al asignar memoria para el nombre de la serie\n");
        free(NuevaSerie);
        return;
    }

    char Nombre[70];
    int Temporadas;
    int capitulos;
    int tiempo;

    // Se ingresan los valores de la nueva serie
    printf("Ingrese el nombre de la serie: \n");
    getchar(); // Para consumir el carácter de nueva línea pendiente
    fgets(Nombre, sizeof(Nombre), stdin);
    Nombre[strcspn(Nombre, "\n")] = '\0';

    if (map_search(ListaSeries, Nombre) != NULL) 
    {
        printf("La serie con el nombre '%s' ya existe en el registro.\n", Nombre);
        free(NuevaSerie->Nombre);
        free(NuevaSerie);
        EnterContinuar();
        return;
    }
    strcpy(NuevaSerie->Nombre, Nombre);

    printf("Ingrese la cantidad de temporadas de la serie: \n");
    scanf("%d", &Temporadas);
    NuevaSerie->Temporadas = list_create();
    if (NuevaSerie->Temporadas == NULL) {
        printf("Error al crear la lista de temporadas\n");
        free(NuevaSerie->Nombre);
        free(NuevaSerie);
        return;
    }

    printf("Ingrese la cantidad de capítulos por temporada:\n");
    scanf("%d", &capitulos);
    NuevaSerie->Completada = false;

    printf("Ingrese la duración de cada capítulo en minutos:\n");
    scanf("%d", &tiempo);

    NuevaSerie->Duracion = 0;

    // Se ingresan los valores de cada temporada
    for(int i = 0; i < Temporadas; i++)
    {
        Temporada *Tempo = (Temporada*)malloc(sizeof(Temporada));
        if (Tempo == NULL) {
            printf("Error al asignar memoria para la temporada\n");
            continue;
        }
        Tempo->Numero = i + 1;
        Tempo->Capitulos = list_create();
        if (Tempo->Capitulos == NULL) {
            printf("Error al crear la lista de capítulos\n");
            free(Tempo);
            continue;
        }
        Tempo->Completada = false;
        Tempo->Duracion = 0; // Inicializamos la duración de la temporada

        for(int j = 0; j < capitulos; j++)
        {
            Capitulo *Cap = (Capitulo*)malloc(sizeof(Capitulo));
            if (Cap == NULL) {
                printf("Error al asignar memoria para el capítulo\n");
                continue;
            }
            Cap->Numero = j + 1;
            Cap->Duracion = tiempo;
            Cap->Completado = false;
            list_pushBack(Tempo->Capitulos, Cap);
            Tempo->Duracion += tiempo; // Sumamos la duración del capítulo a la temporada
        }
        list_pushBack(NuevaSerie->Temporadas, Tempo);
        NuevaSerie->Duracion += Tempo->Duracion;
    }

    map_insert(ListaSeries, NuevaSerie->Nombre, NuevaSerie);
    printf("La serie '%s' ha sido agregada al registro.\n", NuevaSerie->Nombre);
    free(NuevaSerie);
    EnterContinuar();
}


//**************************************************************
//Funcion propia 2
void IngresarEspecial(Map *ListaSeries)
{
    char Nombre[70];
    printf("Ingrese el nombre de la serie: \n");
    getchar(); // Para consumir el carácter de nueva línea pendiente
    fgets(Nombre, sizeof(Nombre), stdin);
    Nombre[strcspn(Nombre, "\n")] = '\0';

    printf("Ingrese el número de la temporada: \n");
    int NumeroTemporada;
    scanf("%d", &NumeroTemporada);

    printf("Ingrese la duración del especial en minutos: \n");
    int tiempo;
    scanf("%d", &tiempo);

    // Buscar la serie en el mapa
    MapPair *seriePair = map_search(ListaSeries, Nombre);
    if (seriePair == NULL) {
        printf("No se encontró la serie especificada.\n");
        EnterContinuar();
        return;
    }
    Serie *serieBuscada = (Serie *)seriePair->value;

    // Buscar la temporada específica
    Temporada *temporada = NULL;
    Temporada *temp = list_first(serieBuscada->Temporadas);
    while (temp != NULL) {
        if (temp->Numero == NumeroTemporada) {
            temporada = temp;
            break;
        }
        temp = list_next(serieBuscada->Temporadas);
    }

    if (temporada == NULL) {
        printf("No se encontró la temporada especificada.\n");
        return;
    }

    // Crear el nuevo capítulo especial
    Capitulo *nuevoCap = (Capitulo *)malloc(sizeof(Capitulo));
    if (nuevoCap == NULL) {
        printf("Error al asignar memoria para el capítulo especial.\n");
        return;
    }
    nuevoCap->Numero = list_size(temporada->Capitulos) + 1;
    nuevoCap->Duracion = tiempo;
    nuevoCap->Completado = false;

    // Agregar el nuevo capítulo a la lista de capítulos de la temporada
    list_pushBack(temporada->Capitulos, nuevoCap);
    temporada->Duracion += tiempo;
    serieBuscada->Duracion += tiempo;

    printf("Capítulo especial agregado exitosamente a la temporada %d de la serie %s.\n", NumeroTemporada, serieBuscada->Nombre);
    EnterContinuar();
}


//*************************************************************
//Funcion propia 3
//en revision

void SeriesSinTerminar(Map *ListaSeries)
{
    
}


//*************************************************************
//Funcion propia 4
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
//*************************************************************
//Funcion propia 5
//en revision
void AvanceSerie(Map *ListaSeries) 
{
  MapPair *Aux;

  char nombreSerie[70];
  printf("Ingrese el nombre de la serie: ");
  getchar();
  fgets(nombreSerie, sizeof(nombreSerie), stdin);
  nombreSerie[strcspn(nombreSerie, "\n")] = '\0';

  Aux = map_search(ListaSeries, nombreSerie);
  if (Aux == NULL)
  {
    printf("No se encontró la serie especificada.\n");
    EnterContinuar();
    return;
  }
  Serie *serie = (Serie *)Aux->value;
  printf("Avance de la Serie: %s\n", serie->Nombre);
  printf("Minutos Vistos = %d\n", serie->TiempoVisto);
  printf("Minutos Restantes = %d\n", (serie->Duracion - serie->TiempoVisto) );
  if(serie->Completada == true)
  {
    printf("------ SERIE COMPLETADA ------\n");
  }
  else
  {
    printf("------ SERIE EN PROGRESO ------\n");
  }

  EnterContinuar();
  

  
  /*
  while (Aux != NULL) 
  {
    
    Serie *serie = (Serie *)Aux->value;
    
    if (strcmp(serie->Nombre, nombreSerie) == 0) 
    {
      int minutosVistos = 0;
      int minutosFaltantes = 0;

      printf("Avance de la serie: %s\n", serie->Nombre);

      Temporada *temporada = list_first(serie->Temporadas);

      while (temporada != NULL) 
      {
        minutosVistos += temporada->TiempoVisto;
        minutosFaltantes += temporada->Duracion - temporada->TiempoVisto;

        temporada = temporada +1;
      }

      printf("Minutos vistos: %d\n", minutosVistos);
      printf("Minutos faltantes: %d\n", minutosFaltantes);

      return;
      EnterContinuar();
    }
      
    Aux = map_next(ListaSeries);
  }*/
}
//*************************************************************
//Funcion propia 6
//en revision
void ActualizarSerie(Map *ListaSeries)
{

  char Nombre[70];
  printf("Ingrese el nombre de la serie: \n");
  getchar(); // Para consumir el carácter de nueva línea pendiente
  fgets(Nombre, sizeof(Nombre), stdin);
  Nombre[strcspn(Nombre, "\n")] = '\0';

  // Buscar la serie en el mapa
  MapPair *seriePair = map_search(ListaSeries, Nombre);
  if (seriePair == NULL) {
      printf("No se encontró la serie especificada.\n");
      return;
  }
  Serie *serieBuscada = (Serie *)seriePair->value;

  printf("Ingrese la cantidad de capítulos que ha visto: ");
  int capitulosVistos;
  scanf("%d", &capitulosVistos);

  int capitulosRestantes = capitulosVistos;
  Temporada *temporada = list_first(serieBuscada->Temporadas);

  while (temporada != NULL && capitulosRestantes > 0) {
      Capitulo *capitulo = list_first(temporada->Capitulos);
      while (capitulo != NULL && capitulosRestantes > 0) {
          if (!capitulo->Completado) {
              capitulo->Completado = true;
              serieBuscada->Duracion -= capitulo->Duracion;
              temporada->Duracion -= capitulo->Duracion;
              capitulosRestantes--;
          }
          capitulo = list_next(temporada->Capitulos);
      }

      // Verificar si la temporada está completada
      bool temporadaCompletada = true;
      capitulo = list_first(temporada->Capitulos);
      while (capitulo != NULL) {
          if (!capitulo->Completado) {
              temporadaCompletada = false;
              break;
          }
          capitulo = list_next(temporada->Capitulos);
      }
      temporada->Completada = temporadaCompletada;

      temporada = list_next(serieBuscada->Temporadas);
  }

  // Verificar si la serie está completada
  bool serieCompletada = true;
  temporada = list_first(serieBuscada->Temporadas);
  while (temporada != NULL) {
      if (!temporada->Completada) {
          serieCompletada = false;
          break;
      }
      temporada = list_next(serieBuscada->Temporadas);
  }
  serieBuscada->Completada = serieCompletada;

  if (serieCompletada) {
      printf("¡Felicidades! Ha completado la serie '%s'.\n", serieBuscada->Nombre);
  } else {
      printf("Actualización realizada. Aún tiene capítulos por ver en la serie '%s'.\n", serieBuscada->Nombre);
  }

  EnterContinuar();
}
//*************************************************************





///////////////////////////////////////////////////////////////////////////

void mostrarMenuPrincipal() 
{
  limpiarPantalla();
  puts("========================================");
  puts("        Registro de Series");
  puts("========================================");

  puts("1) Ingresar al registro de series");
  puts("2) Ver el registro de series");
  puts("3) Ver avance de una serie");
  puts("4) Actualizar el avance de una serie");
  puts("5) Salir");
}

void mostrarMenu1() 
{
  limpiarPantalla();
  puts("========================================");
  puts("        Registro de Series");
  puts("========================================");

  puts("1) Ingresar serie");
  puts("2) Ingresar capitulo especial");
  puts("3) Salir");
}

void mostrarMenu2() 
{
  limpiarPantalla();
  puts("========================================");
  puts("        Registro de Series");
  puts("========================================");

  puts("1) Ver que series faltan por terminar");
  puts("2) Ver que series ya estan terminadas");
  puts("3) Salir");
}



int main(void) 
{
  char opcion; 
  int opcionAux;
  char Nombre[70]; 
  Map *ListaSeries = map_create(is_equal_str);
  List *SeriesTerminadas = list_create();
  do 
    {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) 
    {
    case '1':
      {
        opcionAux = 0;
        mostrarMenu1();
        printf("Ingrese su opción: ");
        scanf("%d", &opcionAux);
        if(opcionAux == 1)
        {
          IngresarSerie(ListaSeries);
        }
        if(opcionAux == 2)
        {
          IngresarEspecial(ListaSeries);
        }
        if(opcionAux == 3)
        {
          break;
        }
      }
      break;
    case '2':
      {
        opcionAux = 0;
        mostrarMenu2();
        printf("Ingrese su opción: ");
        scanf("%d", &opcionAux);
        if(opcionAux == 1)
          {
            SeriesSinTerminar(ListaSeries);
          }
          if(opcionAux == 2)
          {
            SeriesCompletas(ListaSeries);
          }
          if(opcionAux > 2 || opcionAux < 1)
          {
            break;
          }
      }
    case '3':
      {
        limpiarPantalla();
        puts("========================================");
        puts("        Registro de Series");
        puts("========================================");
        puts("Ver el avance de una serie");
        printf("Ingrese el nombre de la serie: ");
        fgets(Nombre, sizeof(Nombre), stdin);
        getchar();
        AvanceSerie(ListaSeries);
        break;
      }
      break;
      case '4':
        {
          limpiarPantalla();
          puts("========================================");
          puts("        Registro de Series");
          puts("========================================");
          puts("Actualizar el avance de una serie");
          printf("Ingrese el nombre de la serie: ");
          fgets(Nombre, sizeof(Nombre), stdin);
          getchar();
          ActualizarSerie(ListaSeries);
          break;
        }
    default:
      break;
    }
      //presioneTeclaParaContinuar();

    } while (opcion != '5');
  return 0;
}