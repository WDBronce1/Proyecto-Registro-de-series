# Sistema de registro de series
## Descripción
  Este codigo se creo con la intencion de poder organizar las series que se estan viendo junto con los tiempos necesarios para terminar cada una segun la duracion total y el avance que el usuario haya hecho en la serie, y para esto se trabajara con las siguientes funciones separadas en diferentes submenus:

    •	Ingresar serie

    •	Ingresar capitulo especial

    •	Ver que series faltan por terminar

    •	Ver que series ya estan terminadas

    •	Ver el avance de una serie

    •	Actualizar el avance de una serie


## Cómo compilar y ejecutar
Para compilar y ejecutar el código, solo hay que presionar el boton "RUN", ubicado en la zona central superior de la pantalla, y el programa se compilara y se ejecutara de manera automatica.

## Funcionalidades
Las funcionalidades de este programa se basan en poder guardar los datos ingresados y unificarlos en una clave de un mapa junto con una lista tanto para la cantidad de temporadas como para la cantidad de capitulos por temporada.
Con la finalidad de poder ubicar las series ingresadas de mejor manera, y con su respectivo estado, ya sea terminada o en progreso, y ordenando segun lo que necesite respectivamente basandose en los datos almacenados, a continuacion se mostrara un ejemplo de uso para cada funcion y que datos necesita cada una para funcionar.


## Ejemplo de uso


### MENU PRINCIPAL 
````
========================================
        Registro de Series
========================================
1) Ingresar al registro de series
2) Ver el registro de series
3) Ver avance de una serie
4) Actualizar el avance de una serie
5) Salir
Ingrese su opción:
````

### SUBMENU 1 (Ingresar al registro de series) (menu principal, opcion 1)
````
========================================
        Registro de Series
========================================
1) Ingresar serie
2) Ingresar capitulo especial
3) Salir
Ingrese su opción:
````
En este submenu se trabaja todo lo relacionado al ingreso de datos.


### INGRESAR SERIE (submenu 1, opcion 1)
````
========================================
        Registro de Series
========================================
1) Ingresar serie
2) Ingresar capitulo especial
3) Salir
Ingrese su opción: 1
Ingrese el nombre de la serie: 
jujutsu kaisen
Ingrese la cantidad de temporadas de la serie: 
2
Ingrese la cantidad de capítulos por temporada:
24
Ingrese la duración de cada capítulo en minutos:
20
La serie 'jujutsu kaisen' ha sido agregada al registro.
Presione Enter para continuar...
````
En esta opcion se ingresa la serie junto con la cantidad de temporadas, capitulos por temporada y tiempo promedio de los capitulos para que sean añadidos al sistema.

### INGRESAR CAPITULO ESPECIAL (submenu 1, opcion 2)
````
========================================
        Registro de Series
========================================
1) Ingresar serie
2) Ingresar capitulo especial
3) Salir
Ingrese su opción: 2
Ingrese el nombre de la serie: 
jujutsu kaisen
Ingrese el número de la temporada: 
2
Ingrese la duración del especial en minutos: 
75
Capítulo especial agregado exitosamente a la temporada 2 de la serie jujutsu kaisen.
Presione Enter para continuar...
````
En esta opcion se selecciona la serie, la temporada a la que corresponde el capitulo especial, y cuanto tiempo dura, para añadir este dato en su correspondiente lugar y sumarle el tiempo de este capitulo a la temporada completa.


### SUBMENU 2 (Ver el registro de series) (menu principal, opcion 2)
````
========================================
        Registro de Series
========================================
1) Ver que series faltan por terminar
2) Ver que series ya estan terminadas
3) Salir
Ingrese su opción:
````
En este menu se trabaja todo lo relacionado a las recopilaciones de series.

### VER QUE SERIES QUE FALTAN POR TERMINAR (submenu 2, opcion 1)
````
========================================
        Registro de Series
========================================
1) Ver que series faltan por terminar
2) Ver que series ya estan terminadas
3) Salir
Ingrese su opción: 1
Series sin terminar (ordenadas de menor a mayor tiempo faltante):
La serie 'chainsaw man' no ha terminado todavía
Tiempo Faltante: 300 minutos
La serie 'tokyo ghoul' no ha terminado todavía
Tiempo Faltante: 900 minutos
Presione Enter para continuar...
````
Al ingresar la opcion, se mostraran las series que aun no se terminan, ordenadas de menor a mayor segun cuanto tiempo hace falta para terminarlas.

### VER QUE SERIES YA ESTAN TERMINADAS (submenu 2, opcion 2)
````
========================================
        Registro de Series
========================================
1) Ver que series faltan por terminar
2) Ver que series ya estan terminadas
3) Salir
Ingrese su opción: 2
Serie: hello kitty, Tiempo de la serie = 120 minutos
Cantidad de series completadas = 1
Presione Enter para continuar...
````
Al ingresar la opcion, se mostraran las series ya completadas, junto con el tiempo total de la serie y un contador con todas las series completadas.

### VER EL AVANCE DE UNA SERIE (menu principal, opcion 3)
````
========================================
        Registro de Series
========================================
Ver el avance de una serie
Ingrese el nombre de la serie: dragon ball
Avance de la Serie: dragon ball
Minutos Vistos = 690
Minutos Restantes = 3630
------ SERIE EN PROGRESO ------
Presione Enter para continuar...
````
Al ingresar el nombre se la serie, se notificara si es que esta terminada o sigue en progreso, y en este ultimo caso mostrara cuantos minutos se han visto y cuantos faltan para terminarla.

### ACTUALIZAR EL AVANCE DE UNA SERIE (menu principal, opcion 4)
````
========================================
        Registro de Series
========================================
Actualizar el avance de una serie
Ingrese el nombre de la serie:
dragon ball
Ingrese la cantidad de capítulos que ha visto: 23
Actualización realizada. Aún tiene capítulos por ver en la serie 'dragon ball'.
Presione Enter para continuar...
````
Para esta funcion se ingresara la serie, y cuantos capitulos se han visto, el programa calculara cuantos minutos corresponden a los capitulos vistos y los restara a la cantidad total de minutos de la serie, la cantidad de minutos vistos y cuantos faltan podran ser vistos en la funcion explicada anteriormente (VER EL AVANCE DE UNA SERIE).
### A CONSIDERAR
````
Se intento separar las funciones principales del archivo main.c, pero generaba muchos errores y complicaba mucho el codigo, pero el codigo funciona correctamente

El compañero Joaquin Rojas no a contribuido en nada para el trabajo, todo a sido hecho por 
Rodrigo Rojas
Nicolas Soto
Agustin Tapia
````