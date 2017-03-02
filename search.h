//
//  serach.h
//  ARQ_TP6


#ifndef serach_h
#define serach_h

#include <stdio.h>
#include "inputOutput.h"

extern pthread_t *threads; //vector de tid

typedef struct th_struct {
    pthread_t tid;
    long long int start;
    long long int end;
}th_struct;


void AC_search();
void save_key(const int estado, const long long int index);
void *multi_AC(void *str);
th_struct *th_init(int N_th);
void cleanup(th_struct* to_matcher);

#endif /* serach_h */
