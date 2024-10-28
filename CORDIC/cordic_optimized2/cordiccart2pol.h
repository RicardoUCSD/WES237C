#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H

#include <ap_fixed.h>

#define NO_ITER 16

typedef int   coef_t;
//typedef float data_t;

typedef ap_fixed<16,3> data_t;//was <16,3 -> error 15,3
//typedef int   data_t;

typedef float acc_t;

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta);

#endif
