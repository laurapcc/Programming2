/******************************************************************************

Nombre del módulo: modelo.c

Descripción: (Descripción breve de la finalidad del módulo)
Funciones de ejemplo de documentación de código para las prácticas de EDI1.

Autor: Jaime Moreno

Fecha: 09-02-2005

Modulos propios que necesita: (Debe incluirse aquí la lista de otros módulos 
que este utilice)
- Módulo 1
- Módulo 2
...

Notas: (Este es el sitio para comentarios de interés sobre el módulo como
aplicación, uso, limitaciones...)

Modificaciones: (Descripción concisa de cada una de las modificaciones 
realizadas, presentadas de forma ordenada e indicando la fecha)
[10-02-2005] Jaime Moreno añade funciones de ejemplo.
[11-02-2005] Jaime Moreno retoca primera funcione de ejemplo.
...

Mejoras pendientes: (Cuando se han detectado problemas en el módulo o aspectos
que se pretenden mejorar, deben explicarse aquí de forma escueta. A medida que
se implementen las mejoras, se quitarán las referencias correspondiente, casi 
siempre para incluirlas en el apartado de Modificaciones)
- Mejora 1
- Mejora 2
...

******************************************************************************/

/*=== Cabeceras =============================================================*/
/* Aquí se incluyen las cabeceras que se necesiten*/
#include <stdlib.h>
#include "modelo.h"

/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: funcionEj1

Descripción: (Descripción breve de la finalidad de la función)
Primera función de ejemplo que no hace nada.

Argumentos de entrada: (Enumeración de los argumentos por orden de aparición en
el prototipo indicando para que sirven)
1. nmr, número entero para pasar ...
2. cdn, puntero a una cadena de caracteres para...

Retorno: (Enumeración de los valores que puede devolver la función indicando en
que circunstancias)
- 0, si se ha terminado sin problemas
- Número negatico en caso contrario, en particular -1 si el primer argumento
es demasiado grande, -2 si el segundo argumento es nulo y -3 en cualquier otro
caso.

-----------------------------------------------------------------------------*/

int funcionEj1(int nmr, char* cdn) {
	...
	while (nmr > i) { 
	
		... /* Comentario al final de la línea para aclar su sentido */
		
		while (nmr == j) { 
			...
			/*** Comentario en una línea para aclarar código siguiente ***/
			... 
			
			if (nmr > 0) { 
			
			} 
			
			else { 
			
			} 
		
		} /* fin del while estado */ 
	
	} /* fin del while entrada */
	/*** NO UTILIZAR COMENTARIOS AL ESTILO C+ ***/
	...
return 0;
}

/*-----------------------------------------------------------------------------

Nombre: funcionEj2

Descripción: Segunda función de ejemplo que no hace nada.

Argumentos de entrada: Ninguno

Retorno:
- 0 si se ha terminado sin problemas
- Un -1 si se ha terminado con un error.

-----------------------------------------------------------------------------*/

int funcionEj2() {
	...
return 0;
}

/*****************************************************************************/