//
//  inputOutput.h
//  ARQ_TP6


#ifndef inputOutput_h
#define inputOutput_h

#include "stateMachine.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern char *text;//guarda texto a analizar
extern long long int txt_len;
extern int nk; //numero de claves

//vector de resultados primera dimension son nk claves y segunda son indices donde se encuentra esa clave
extern long long int **results;
extern int *n_results; //controla cuantos resultados hay de cada tipo


void print_stdout();
void file_out();
void read_keys(char *path);
void read_text(char *path);

int cmpfunc (const void * a, const void * b);


#endif /* inputOutput_h */
