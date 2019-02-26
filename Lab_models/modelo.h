#ifndef _MODELO_H
#define _MODELO_H
/******************************************************************************

Nombre del fichero: modelo.h

Nombre del módulo correspondiente: modulo.c

Descripción: (Descripción breve de la finalidad del fichero)
Cabeceras del módulo Modelo para las prácticas de EDI1.

(Nota: en el ifndef y el define del principio hay que poner una cadena que
incluya el nombre del fichero , en este caso _MODULO_H, pero si se tratara
del fichero ejemplo.h sería _EJEMPLO_H)

******************************************************************************/

/*=== Cabeceras =============================================================*/
/* Aquí se incluyen las cabeceras que se necesiten*/

/*=== Definiciones ==========================================================*/
/* Aquí se incluyen las definiciones de tipos y constantes requeridos*/

# define MAX_LINEA 256

typedef enum {
	BIEN, MAL
} TEstado;

typedef struct {
	int ancho;
	int alto;
} TEjemplo;

/*=== Prototipos de Funciones ===============================================*/

/*-----------------------------------------------------------------------------
(Descripción de la función con el formato "Nombre_Función: Descripción_Breve")
funcionEj1: Primera función de ejemplo que no hace nada.
-----------------------------------------------------------------------------*/
int funcionEj1(int nmr, char* cdn);

/*-----------------------------------------------------------------------------
funcionEj2: Segunda función de ejemplo que no hace nada.
-----------------------------------------------------------------------------*/
int funcionEj2();

/*****************************************************************************/
#endif