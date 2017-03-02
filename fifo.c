//
//  fifo.c
//  ARQ_TP6
//


#include "fifo.h"
#include <stdlib.h>
#include <stdio.h>

const int fifo_max = NCHARS;
int elementos = 0;
int inicio = 0;
int final = -1;
int fifo[NCHARS];

void fifo_add(int i){
    
    if (elementos == 26)
        printf("error de dimensionado, cola FIFO llena\n");
    else{
        if (final == (26 - 1))
            final = -1;
        
        elementos++;
        fifo[++final] = i;
    }
}

int fifo_out(){
    int out = fifo[inicio++];
    
    if(inicio == 26)
        inicio = 0;
    
    elementos--;
    return out;
}

