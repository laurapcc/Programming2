/*
 * File:   functions.h
 * Author: Paula Samper, Laura de Paz
 */


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"

void string_destroy(void* e);
void * string_copy(const void *e);
int string_cmp(const void* e1, const void* e2);
void * string_ini ();

#endif /* FUNCTIONS_H_*/
