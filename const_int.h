// --------------------------------------------------------------------
// const_int.h
// --------------------------------------------------------------------

#ifndef CONST_INT_H
#define CONST_INT_H

// application defaults
#define Application_Name            "Pyramids"
#define Version_String              "version 1.00"

#define Debug_File_Name_Default     "#log.txt"
#define Execution_Directory_Default "."
#define Shared_Memory_Unique_Label  "180770"

// optional modules (can be compiled without them)
#define HTTPGET_MODULE  0
#define CHKHEAP_MODULE  0

#if (HTTPGET_MODULE!=0)
#define Quotes_Http_Server          "http://ivyjoy.com/quote.shtml"
// well, it should be internal const or really parameter...
#endif

#endif // CONST_INT_H
