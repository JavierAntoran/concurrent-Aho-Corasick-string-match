//
//  stateMachine.c
//  ARQ_TP6


#include "stateMachine.h"
#include <stdlib.h>
#include <string.h>

int longest_key = 0;
int **go; //goto function [estados][letra_abecedario]
int *out; //output vector: tendremos un 1 en la posicion en la que se encuentre el acierto
int *fail; //fail function
int snk; //suma de longitud de todas las palabras clave + 1
char **keys;//guarda palabras clave


int build_roboto(){ //construye maquina estados//devuelve el numero de estados
    
    char *key;
    int estados = 1; //partimos del estado 0 es decir, hay 1 estado
    int current_state = 0;
    unsigned int key_len;
    int c; //representa el caracter desde 0 a 25
    
    //alocamos variables para maquina estados
    out = malloc(sizeof(int) * snk);
    memset(out, 0, sizeof(int) *snk);
    fail = malloc(sizeof(int) * snk);
    memset(fail, -1, sizeof(int) * snk);//-1 significa no transicion
    
    go = (int**) malloc(sizeof(int*) * snk);
    for(int i = 0; i < snk; i++){
        go[i] = malloc(sizeof(int) * NCHARS);
        memset(go[i], -1, sizeof(int) * NCHARS);//-1 significa no transicion
    }
    
    //construimos arbol, asignaciones goto
    for(int i = 0; i < nk; i++){ //recorremos todas las palabras clave
        key = keys[i];
        key_len = strlen(key); //perdida de precisiin ok porque no esperamos palabras demasiado grandes en principio
        current_state = 0;
        
        for(int j = 0; j < key_len; j++){//recorremos palabra sin coger el '\0'
            c = (key[j] - 'a'); //devuelve int
            
            if(go[current_state][c] == -1){//si caracter no en tabla
                go[current_state][c] = estados; //añadimos nuevo estado
                estados++;
            }
            current_state = go[current_state][c]; //actual es el ultimo añadido
        }//fin bucle interior
        
        out[current_state] |= (1<<i); //añadimos palabra actual a funcion de salida en su posicion
    }
    
    //mandamos a 0 todas las letras que no tengan palabra en estado 0
    for(int n = 0; n < NCHARS; n++){
        if(go[0][n] == -1)
            go[0][n] = 0;
    }
    
    //implementamos funcion de fallo --> requiere implementacion FIFO <-- se puede unir a bucle anterior pero asi es mas facil de ver
    //crear FIFO
    for(int n = 0; n < NCHARS; n++){
        if(go[0][n] != 0){
            fail[go[0][n]] = 0;
            fifo_add(go[0][n]); //fifo paper
        }
    }
    
    int estado = 0;
    int fallo = 0;
    
    while(elementos != 0){ //mientras haya elementos en fifo
        
        estado = fifo_out();//fifo[inicio];
        
        for (int n = 0; n < NCHARS; n++){
            
            if(go[estado][n] != -1){
                fallo = fail[estado];
                while(go[fallo][n] == -1)
                    fallo = fail[fallo];
                
                fallo = go[fallo][n];
                fail[go[estado][n]] = fallo;
                
                out[go[estado][n]] |= out[fallo];
                fifo_add(go[estado][n]);
            }
        }
    }
    
    return estados;
}

int next_estado(int estado_actual, char entrada){//funcion de transicion de estados
    
    char ch = (entrada - 'a');
    int estado = estado_actual;
    
    while(go[estado][ch] == -1) //busqueda por funcion de goto y fallo
        estado = fail[estado];
    
    return go[estado][ch];
}

