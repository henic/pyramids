
#include <malloc.h>
#include <QDebug>

#include "chkheap.h"

#if CHKHEAP_MODULE==1

void check_heap(char *file, int line)
{
    static char *lastOkFile = (char*)"here";
    static int lastOkLine = 0;
    static int heapOK = 1;

    if (!heapOK) return;

    if (_heapchk() == _HEAPOK)
    {
        lastOkFile = file;
        lastOkLine = line;
       return;
    }

    heapOK = 0;
    qCritical() << "Heap corruption detected at file" << file <<
                   ", line " << line << "\nLast OK at file " <<
                   lastOkFile << ", line " << lastOkLine;
}

#endif //chkheap_module
