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
#include "TDAs/queue.h"

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

//Esta función compara dos strings (char *) para determinar si son iguales.
int is_equal_str(void *key1, void *key2) 
{
  return strcmp((char *)key1, (char *)key2) == 0;
}

//Imprime un mensaje y espera a que el usuario presione Enter dos veces para continuar.
void EnterContinuar()
{
    printf("Presione Enter para continuar...");
    getchar(); 
    getchar(); 
}

//Permite al usuario ingresar una nueva serie con detalles como nombre, cantidad de temporadas, cantidad de capítulos por temporada y duración de cada capítulo.
void IngresarSerie(Map *ListaSeries) {
    Serie *NuevaSerie = (Serie *)malloc(sizeof(Serie));
    if (NuevaSerie == NULL) {
        printf("Error al asignar memoria para la nueva serie\n");
        return;
    }

    NuevaSerie->Nombre = (char *)malloc(70 * sizeof(char));
    if (NuevaSerie->Nombre == NULL) {
        printf("Error al asignar memoria para el nombre de la serie\n");
        free(NuevaSerie);
        return;
    }

    char Nombre[70];
    int Temporadas;
    int capitulos;
    int tiempo;

    printf("Ingrese el nombre de la serie: \n");
    getchar();
    fgets(Nombre, sizeof(Nombre), stdin);
    Nombre[strcspn(Nombre, "\n")] = '\0';

    if (map_search(ListaSeries, Nombre) != NULL) {
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
    NuevaSerie->TiempoVisto = 0;

    for (int i = 0; i < Temporadas; i++) {
        Temporada *Tempo = (Temporada *)malloc(sizeof(Temporada));
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
        Tempo->Duracion = 0;
        Tempo->TiempoVisto = 0;

        for (int j = 0; j < capitulos; j++) {
            Capitulo *Cap = (Capitulo *)malloc(sizeof(Capitulo));
            if (Cap == NULL) {
                printf("Error al asignar memoria para el capítulo\n");
                continue;
            }
            Cap->Numero = j + 1;
            Cap->Duracion = tiempo;
            Cap->Completado = false;
            list_pushBack(Tempo->Capitulos, Cap);
            Tempo->Duracion += tiempo;
        }
        list_pushBack(NuevaSerie->Temporadas, Tempo);
        NuevaSerie->Duracion += Tempo->Duracion;
    }

    map_insert(ListaSeries, NuevaSerie->Nombre, NuevaSerie);
    printf("La serie '%s' ha sido agregada al registro.\n", NuevaSerie->Nombre);
    EnterContinuar();
}

//Permite al usuario ingresar un capítulo especial para una serie existente especificando el nombre de la serie, número de temporada y duración del especial.
void IngresarEspecial(Map *ListaSeries) {
    char Nombre[70];
    printf("Ingrese el nombre de la serie: \n");
    getchar();
    fgets(Nombre, sizeof(Nombre), stdin);
    Nombre[strcspn(Nombre, "\n")] = '\0';

    printf("Ingrese el número de la temporada: \n");
    int NumeroTemporada;
    scanf("%d", &NumeroTemporada);

    printf("Ingrese la duración del especial en minutos: \n");
    int tiempo;
    scanf("%d", &tiempo);

    MapPair *seriePair = map_search(ListaSeries, Nombre);
    if (seriePair == NULL) {
        printf("No se encontró la serie especificada.\n");
        EnterContinuar();
        return;
    }
    Serie *serieBuscada = (Serie *)seriePair->value;

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
        EnterContinuar();
        return;
    }

    Capitulo *nuevoCap = (Capitulo *)malloc(sizeof(Capitulo));
    if (nuevoCap == NULL) {
        printf("Error al asignar memoria para el capítulo especial.\n");
        EnterContinuar();
        return;
    }
    nuevoCap->Numero = list_size(temporada->Capitulos) + 1;
    nuevoCap->Duracion = tiempo;
    nuevoCap->Completado = false;

    list_pushBack(temporada->Capitulos, nuevoCap);
    temporada->Duracion += tiempo;
    serieBuscada->Duracion += tiempo;

    printf("Capítulo especial agregado exitosamente a la temporada %d de la serie %s.\n", NumeroTemporada, serieBuscada->Nombre);
    EnterContinuar();
}

//Función de comparación utilizada en la ordenación (qsort) de las series según el tiempo restante para completarlas.
int compararTiempoFaltante(const void *a, const void *b) {
    Serie *serieA = *(Serie **)a;
    Serie *serieB = *(Serie **)b;

    int tiempoFaltanteA = serieA->Duracion - serieA->TiempoVisto;
    int tiempoFaltanteB = serieB->Duracion - serieB->TiempoVisto;

    return tiempoFaltanteA - tiempoFaltanteB;
}

//Lista las series que no han sido completadas ordenadas por el tiempo faltante para terminarlas.
void SeriesSinTerminar(Map *ListaSeries) {
    
    int numSeriesSinTerminar = 0;

    MapPair *aux = map_first(ListaSeries);
    while (aux != NULL) {
        Serie *serieActual = (Serie *)aux->value;
        if (!serieActual->Completada) {
            numSeriesSinTerminar++;
        }
        aux = map_next(ListaSeries);
    }

    Serie **seriesSinTerminar = (Serie **)malloc(numSeriesSinTerminar * sizeof(Serie *));
    if (seriesSinTerminar == NULL) {
        printf("Error: No se pudo asignar memoria para la lista temporal.\n");
        return;
    }

    int index = 0;
    aux = map_first(ListaSeries);
    while (aux != NULL) {
        Serie *serieActual = (Serie *)aux->value;
        if (!serieActual->Completada) {
            seriesSinTerminar[index++] = serieActual;
        }
        aux = map_next(ListaSeries);
    }

    qsort(seriesSinTerminar, numSeriesSinTerminar, sizeof(Serie *), compararTiempoFaltante);

    printf("Series sin terminar (ordenadas de menor a mayor tiempo faltante):\n");
    for (int i = 0; i < numSeriesSinTerminar; i++) {
        Serie *serie = seriesSinTerminar[i];
        printf("La serie '%s' no ha terminado todavía\n", serie->Nombre);
        printf("Tiempo Faltante: %d minutos\n", serie->Duracion - serie->TiempoVisto);
    }

    free(seriesSinTerminar); 
    EnterContinuar();
}

//Imprime las series que ya han sido completadas junto con su duración total.
void SeriesCompletas(Map *ListaSeries) {
    int SeriesCompletadas = 0;
    MapPair *Aux = map_first(ListaSeries);

    while (Aux != NULL) {
        Serie *Series = (Serie *)Aux->value;
        if (Series->Completada) {
            SeriesCompletadas++;
            printf("Serie: %s, Tiempo de la serie = %d minutos\n", Series->Nombre, Series->Duracion);
        }
        Aux = map_next(ListaSeries);
    }
    printf("Cantidad de series completadas = %d\n", SeriesCompletadas);
    EnterContinuar();
}

//Muestra el avance actual de una serie específica en términos de minutos vistos, minutos restantes y si la serie está completada o no.
void AvanceSerie(Map *ListaSeries) {
    char nombreSerie[70];
    printf("Ingrese el nombre de la serie: ");

    fgets(nombreSerie, sizeof(nombreSerie), stdin);
    nombreSerie[strcspn(nombreSerie, "\n")] = '\0';

    MapPair *Aux = map_search(ListaSeries, nombreSerie);
    if (Aux == NULL) {
        printf("No se encontró la serie especificada.\n");
        EnterContinuar();
        return;
    }
    Serie *serie = (Serie *)Aux->value;
    printf("Avance de la Serie: %s\n", serie->Nombre);
    printf("Minutos Vistos = %d\n", serie->TiempoVisto);
    printf("Minutos Restantes = %d\n", serie->Duracion - serie->TiempoVisto);
    if (serie->Completada) {
        printf("------ SERIE COMPLETADA ------\n");
    } else {
        printf("------ SERIE EN PROGRESO ------\n");
    }

    EnterContinuar();
}

//Permite al usuario actualizar el avance de una serie específica marcando los capítulos como completados.
void ActualizarSerie(Map *ListaSeries) {
    char Nombre[70];
    printf("Ingrese el nombre de la serie:\n");
    fgets(Nombre, sizeof(Nombre), stdin);
    Nombre[strcspn(Nombre, "\n")] = '\0';

    MapPair *seriePair = map_search(ListaSeries, Nombre);
    if (seriePair == NULL) {
        printf("No se encontró la serie especificada.\n");
        EnterContinuar();
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
                serieBuscada->TiempoVisto += capitulo->Duracion;
                capitulosRestantes--;
            }
            capitulo = list_next(temporada->Capitulos);
        }

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

//Muestran los diferentes menús de opciones disponibles al usuario.
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


//Es la función principal que controla el flujo del programa. Aquí se realizan las llamadas a las funciones según la opción seleccionada por el usuario hasta que decide salir.
int main(void) 
{
  char opcion; 
  int opcionAux;
  char Nombre[70]; 
  Map *ListaSeries = map_create(is_equal_str);
  List *SeriesTerminadas = list_create();
  do 
    {
      opcionAux = 0;
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
        break;
      }
    case '3':
      {
        limpiarPantalla();
        puts("========================================");
        puts("        Registro de Series");
        puts("========================================");
        puts("Ver el avance de una serie");
        fgets(Nombre, sizeof(Nombre), stdin);
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
          fgets(Nombre, sizeof(Nombre), stdin);
          ActualizarSerie(ListaSeries);
          break;
        }
    default:
      break;
    }

    } while (opcion != '5');
  return 0;
}