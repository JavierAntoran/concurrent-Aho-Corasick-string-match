//
//  fifo.h
//  ARQ_TP6


#ifndef fifo_h
#define fifo_h
#define NCHARS 26


extern const int fifo_max;
extern int elementos;

void fifo_add(int i);
int fifo_out();

#endif /* fifo_h */
