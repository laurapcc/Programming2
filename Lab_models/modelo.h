#ifndef _MODELO_H
#define _MODELO_H
/******************************************************************************

Nombre del fichero: modelo.h

Nombre del m�dulo correspondiente: modulo.c

Descripci�n: (Descripci�n breve de la finalidad del fichero)
Cabeceras del m�dulo Modelo para las pr�cticas de EDI1.

(Nota: en el ifndef y el define del principio hay que poner una cadena que
incluya el nombre del fichero , en este caso _MODULO_H, pero si se tratara
del fichero ejemplo.h ser�a _EJEMPLO_H)

******************************************************************************/

/*=== Cabeceras =============================================================*/
/* Aqu� se incluyen las cabeceras que se necesiten*/

/*=== Definiciones ==========================================================*/
/* Aqu� se incluyen las definiciones de tipos y constantes requeridos*/

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
(Descripci�n de la funci�n con el formato "Nombre_Funci�n: Descripci�n_Breve")
funcionEj1: Primera funci�n de ejemplo que no hace nada.
-----------------------------------------------------------------------------*/
int funcionEj1(int nmr, char* cdn);

/*-----------------------------------------------------------------------------
funcionEj2: Segunda funci�n de ejemplo que no hace nada.
-----------------------------------------------------------------------------*/
int funcionEj2();

/*****************************************************************************/
#endif