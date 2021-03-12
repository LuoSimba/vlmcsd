#ifndef INCLUDED_OUTPUT_H
#define INCLUDED_OUTPUT_H

#include "config.h"

#include <errno.h>
#include "types.h"
#include "kms.h"

typedef int (*PRINTFUNC)(const char *const fmt, ...);

int printerrorf(const char *const fmt, ...);
int errorout(const char* fmt, ...);
void logRequestVerbose(REQUEST* Request, const PRINTFUNC p);
void logResponseVerbose(const char *const ePID, const BYTE *const hwid, RESPONSE* response, const PRINTFUNC p);

void printCommonFlags();
void printServerFlags();
void printClientFlags();

#ifndef NO_LOG
int logger(const char *const fmt, ...);
#endif //NO_LOG

void uuid2StringLE(const GUID *const guid, char *const string);

//void copy_arguments(int argc, char **argv, char ***new_argv);
//void destroy_arguments(int argc, char **argv);

#endif // INCLUDED_OUTPUT_H
