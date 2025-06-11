#ifndef __PINC_H__
#define __PINC_H__

#define MAX_HEADERS 64

typedef enum {
  HTTP,
  HTTPS
} httpProtocol;

typedef struct {
  char *key;
  char *value;
} httpHeader;


typedef struct {
  int status;
  httpHeader *headers;
  size_t headerLen;
  char *body;
} httpResponse;

#endif
