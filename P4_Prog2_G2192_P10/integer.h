/*
 * File:   integer.h
 * Author: Paula Samper, Laura de Paz
 */


#ifndef INTEGER_H
#define INTEGER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "types.h"

extern int errno;



void int_destroy(void* e);

void * int_copy(const void* e);

int int_print(FILE * f, const void* e);

int int_cmp(const void* e1, const void* e2);

void * int_ini ();

void * int_setInfo (void *e, int v);



#endif /* INTEGER_H_ */
