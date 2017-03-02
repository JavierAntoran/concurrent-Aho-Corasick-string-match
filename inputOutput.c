//
//  inputOutput.c
//  ARQ_TP6


#include "inputOutput.h"

char *text;
long long int txt_len;
int nk; //numero de claves

long long int **results;
int *n_results; //controla cuantos resultados hay de cada tipo

void read_keys(char *path){
    
    int fd;
    int i = 0;
    int j = 0;//cuenta total de caracteres
    int lineas = 1;
    int max_linesize = 1000; //un linesize infinito requiere recorrer 2 veces
    char c;
    
    keys = (char**) malloc(sizeof(char*)*lineas);
    keys[lineas-1] = malloc(sizeof(char)*max_linesize);
    
    if((fd = open(path, O_RDONLY)) == -1)
        printf("error abriendo archivo claves\n");
    
    while( read(fd, &c, 1) > 0){//-1 es error y 0 es EOF
        
        if((c == '\n') || (c == '\r')){
            *(keys[lineas-1]+i) = '\0';
            lineas++;
            if (i > longest_key)
                longest_key = i;
            i = 0;
            keys = (char**) realloc(keys, sizeof(char*)*lineas);
            keys[lineas-1] = malloc(sizeof(char)*max_linesize);
            
        }else{
            
            *(keys[lineas-1]+i) = c;
            i++;
            j++;
        }
    }
    if(*keys[lineas-1] == '\0'){
        //printf("eliminando retorno de carro extra de entrada\n");
        free(keys[lineas-1]);
        lineas--;
    }
    
    nk = lineas;
    snk = j+1;
    close(fd);
    
    
}

void read_text(char *path){
    //lee texto y lo guarda en strin global text
    int fd;
    
    if( (fd = open(path, O_RDONLY)) == -1){
        printf("error abriendo archivo text\n");
        exit(1);
    }
    
    long long int size = lseek(fd, 0, SEEK_END);
    text = malloc(size*sizeof(char));
    lseek(fd, 0, SEEK_SET);
    
    if( size != read(fd, text, size) )
        printf("no se ha leido todo el texto\n");
    
    close(fd);
}

void print_stdout(){
    
    for(int u=0;u<nk;u++){
        printf("%s\t\t%d\n",keys[u],n_results[u]);
    }
    
}

void file_out(){
    
    for(int u=0;u<nk;u++){
        printf("%s\t\t",keys[u]);
        printf("%d\t",n_results[u]);
        for(int j=0;j<(n_results[u]);j++){
            printf("%llu\t",results[u][j]);
        }
        printf("\n");
    }
    
}

int cmpfunc (const void * a, const void * b){
    int va = *(const int*) a;
    int vb = *(const int*) b;
    return (va > vb) - (va < vb);
}
