#ifndef CHKHEAP_H
#define CHKHEAP_H

#include "const_int.h"

#if CHKHEAP_MODULE==1

void check_heap (char *file, int line);

#define CHKHEAP()  (check_heap(__FILE__, __LINE__))

#endif

#endif // CHKHEAP_H
