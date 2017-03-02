//
//  stateMachine.h
//  ARQ_TP6


#ifndef stateMachine_h
#define stateMachine_h

#include "fifo.h"
extern int **go; //goto function [estados][letra_abecedario]
extern int *out; //output vector: tendremos un 1 en la posicion en la que se encuentre el acierto
extern int *fail; //fail function
extern int nk; //numero de claves
extern int longest_key;
extern int snk; //suma de longitud de todas las palabras clave + 1
extern char **keys;//guarda palabras clave


int next_estado(int estado_actual, char entrada);
int build_roboto();

#endif /* stateMachine_h */
