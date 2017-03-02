//
//  main.c
//  ARQ_TP6
//

#include "search.h"

#include <sys/time.h>
#include <pthread.h>

int main(int argc, const char **argv){
    
    
    const char *text_path;
    const char *keys_path;
    int N_th;
    int j;
    
    //Variables para salidas
    struct timeval ti,tf;
    double t_before,t_search,t_after;
    
        if (argc != 4){
            printf("3 arguments required\n ej: ./main text.in keys.in n_threads\n");
            exit(1);
        }
    
    text_path = *(argv+1);
    keys_path = *(argv+2);
    N_th = atoi(*(argv+3));
    
    gettimeofday(&ti,NULL);//Instante inicial de Tbefore
    
    read_keys(keys_path);
    read_text(text_path);
   
    //cpnstruimos maquina estados
    build_roboto();
    
    gettimeofday(&tf,NULL);//Instante final de Tbefore
    t_before = ((tf.tv_usec - ti.tv_usec) + ((tf.tv_sec - ti.tv_sec)*1000000.0f));
    gettimeofday(&ti,NULL);//Instante inicial de TSearch
    
    th_struct *mi_struct;
    
    if (N_th == 1){
        mi_struct = th_init(N_th);
        //printf("mi puta vida\n");
        AC_search();
        //printf("mi puta vidav2\n");
    }
    else{
    //comenzamos busqueda
        mi_struct = th_init(N_th);
        
        for(int i = 0; i<N_th; i++){
            pthread_join(threads[i],NULL); //creo que existe alternativa a esto que no bloquea
        }
}

    
    gettimeofday(&tf,NULL);//Instante final de TSearch
    t_search = ((tf.tv_usec - ti.tv_usec) + ((tf.tv_sec - ti.tv_sec)*1000000.0f));
    gettimeofday(&ti,NULL);//Instante inicial de TAfter
    
    for(j = 0; j < nk; j++){
        qsort(results[j], n_results[j], sizeof(long long int), cmpfunc);
    }
    
    print_stdout();
    close(1);
    int fd = creat("salida.out", 0666);
    file_out();
    close(fd);
    
    cleanup(mi_struct);
    
    gettimeofday(&tf,NULL);//Instante final de TAfter
    t_after = ((tf.tv_usec - ti.tv_usec) + ((tf.tv_sec - ti.tv_sec)*1000000.0f));
    
    fprintf(stderr,"times in nanoseconds (setup search cleanup): \t%g\t%g\t%g\n",t_before,t_search,t_after);
    
    return 0;
}
