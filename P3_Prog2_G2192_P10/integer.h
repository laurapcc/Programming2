/*
 * File:   integer.h
 * Author: Paula Samper, Laura de Paz
 */


#ifndef NODE_H_
#define NODE_H_

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

#endif /* NODE_H_ */
