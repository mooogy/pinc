#include "internal/parse.h"
#include <string.h>
#include <stdlib.h>

int parseStatusCode(const char *raw, int *responseStatus, char **headersStart) {
  char *statusCodeStart = strchr(raw, ' ') + 1; // find ' ' before the status code and skip the ' '
  if (!statusCodeStart) { // Status code section malformed
    return -1;
  }

  *responseStatus = atoi(statusCodeStart); // set status code of response
  if (*responseStatus == 0) { // Status code not found
    return -1;
  }

  char *statusCodeEnd = strstr(statusCodeStart, "\r\n"); // find the end of the status code line
  if (!statusCodeEnd) { // End of status code section not found
    return -1;
  }
  *headersStart = statusCodeEnd + 2; // Set headersStart to where headers begin

  return 0;
}
