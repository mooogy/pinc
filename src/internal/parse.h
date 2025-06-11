#ifndef __PINC_PARSE_H__
#define __PINC_PARSE_H__
#include "../../include/pinc.h"

int parseStatusCode(const char *raw, int *responseStatus, char **headersStart);
int parseHeaders(const char *raw, httpHeader *headers, char **bodyStart);

#endif
