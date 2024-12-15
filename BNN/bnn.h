#ifndef __BNN_HEADER_
#define __BNN_HEADER_
#include <iostream>

using namespace std;

#include "ap_int.h"
#define DEBUG 1 



//Yoy can change SIZE and function prototype if needed.
typedef  const unsigned int DTYPE; // used as an input type
typedef  int ITYPE;                // used as an output type

const int SIZE = 25;
void bnn(DTYPE IN[SIZE], ITYPE ys[10]);
//ITYPE XNOR(ITYPE x0, ITYPE x1);
unsigned int XNOR(unsigned int a, unsigned int b);

#endif
