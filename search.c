//
//  serach.c
//  ARQ_TP6


#include "search.h"
#include <pthread.h>

pthread_mutex_t *m;//vectir mutexes
pthread_t *threads; //vector de tid

void AC_search(){ //Search function with one thread
    
    txt_len = strlen(text);
    int estado = 0;
    long int x_index; //indice encontradp
    char *x_key; //clave encontrada
    
    for(long long int i = 0; i < txt_len; i++){//bucle principal
        
        estado = next_estado(estado, text[i]);
        
        if(out[estado] != 0){
            for(int j = 0; j < nk; j++){
                if (out[estado] & (1<<j)){//condicion separada de bucle por si hay dos palabras que acaban en mismo estado
                    x_key = keys[j];
                    x_index = i - strlen(x_key) + 1;
                    results[j][n_results[j]] = x_index;
                    n_results[j]++;
                }
            }
        }
    }
} //para 1 thread, No utilizado

void save_key(const int estado, const long long int index){
    
    long long int x_index; //indice encontradp
    char *x_key; //clave encontrada
    int i;
    
    for(int j = 0; j < nk; j++){
        if (out[estado] & (1<<j)){//condicion separada de bucle por si hay dos palabras que acaban en mismo estado
            x_key = keys[j];
            x_index = index - strlen(x_key) + 1;
            
            pthread_mutex_lock(m + j);//bloqueamos solo clave en cuestion solo si zona conflictiva
            for(i = 0; ( (results[j][i] != x_index) && (i < n_results[j]) ); i++); //buscamos si ya esta escrito el resultado
            
            if (results[j][i] == x_index);//aseguramos que no es duplicado
            else if(i == n_results[j]){
                results[j][i] = x_index;//guardamos resultado
                n_results[j]++;//sumanos a la cuenta resultados
                //printf("palabra encontrada: %s en posicion %lld \n", x_key, x_index);
            }
            else{
                printf("no deberiamos llegar aqui nunca: error guardando resultados\n");
                exit(100);
            }
            
            pthread_mutex_unlock(m + j);
        }
        
    }
}

void *multi_AC(void *str){ //implementacion para multiples threads
    long long int start =  ((struct th_struct *)str)->start;
    long long int end = ((struct th_struct *)str)->end;
    
    int estado = 0;
    long long int max_overlap = end + longest_key;
    if (max_overlap > txt_len)
        max_overlap = txt_len;
    
    
    for(long long int i = start; ( ((i < end)||(estado != 0)) && (i < max_overlap) ); i++){//bucle principal
        
        estado = next_estado(estado, text[i]); //actualizamos estado
        
        if(out[estado] != 0){//detectamos coincidencia
            save_key(estado, i);
        }
    }
    return NULL;
}

th_struct *th_init(int N_th){
    
    int i;
    
    //vars para guardado informacion en threads:
    
    int espacio_inicial = 1000; //espacio para vector resultados inicial podria hacerse dinamico (evita reallocs)
    
    results = (long long int **) malloc(sizeof(long long int *) * nk);// vector de resultados solo con threads
    n_results = (int *) malloc(sizeof(int) * nk); //vector que controlara espacio para escribir resultados
    memset(n_results, 0, sizeof(int) * nk);
    m = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nk);//tantos mutexes como claves muahahahahaha
    
    for (int i = 0; i < nk; i++){
        
        pthread_mutex_init(m+i, NULL); //inicilizamos mutexes
        
        results[i] = (long long int*) malloc(sizeof(long long int) * espacio_inicial); // suponemos dos resultados
        memset(results[i], -1, sizeof(long long int) * espacio_inicial);
    }
    
    //VARS para division de texto en N partes suponiendo N threads
    txt_len = strlen(text);
    
    //printf("long text: %lld\n", txt_len);
    
    long long int lngth = txt_len / N_th;
    int resto = txt_len % N_th;
    
    long long int thread_length; // he cambiado el mombre porque se confundia un poco
    long long int start;
    long long int last_start=0;
    
    //Alocamos vars para ejecucion threads
    struct th_struct *to_matcher; //variable que pasaremos a los threads
    to_matcher = (th_struct *) malloc(sizeof(th_struct) * N_th);
    
    threads = (pthread_t *) malloc(sizeof(pthread_t) * N_th);
    if (N_th != 1){
        //bucle generacion estructuras argumento para threads
        for (i = 0; i < N_th; i++) {//Creamos threads
            
            if(resto!=0){
                thread_length = lngth + 1; //compensamos desigualdades en carga de los threads
                resto--;
            }else{
                thread_length = lngth;
            }
            //asignamos puntos de inicio y fin de busqueda para cada thread
            start = last_start;
            last_start = start+thread_length;
            to_matcher[i].start=start;
            to_matcher[i].end=last_start;
            //lanzamos threads
            
            if( pthread_create(&threads[i], NULL, multi_AC ,(void*) &to_matcher[i]) )
                printf("thread error when creating thread\n");
        }
    }
    return to_matcher;
}

void cleanup(th_struct* to_matcher){
    
    int i;
    
    free(text);
    for(i = 0; i<nk; i++){
        
        free(*(keys + i));
        free(*(results+i));
        pthread_mutex_destroy(m + i);
    }
    free(results);
    free(keys);
    free(out);
    free(fail);
    for(i = 0; i < snk; i++)
        free(*(go + i));
    free(go);
    free(n_results);
    free(m);
    free(threads);
    free(to_matcher);
    
    
}

