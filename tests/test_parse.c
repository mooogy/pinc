#include "../src/internal/parse.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

// Include your internal header
#include "../src/internal/parse.h"


void test_valid_status(void) {
    const char* raw = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
    int status = 0;
    char* next = NULL;

    int result = parseStatusCode(raw, &status, &next);

    assert(result == 0);
    assert(status == 404);
    assert(next != NULL);
    assert(strncmp(next, "Content-Type: text/html\r\n\r\n", 26) == 0);
}

void test_valid_200(void) {
    const char* raw = "HTTP/1.1 200 OK\r\nDate: Sun, 09 Jun 2024 12:00:00 GMT\r\n\r\n";
    int status = 0;
    char* next = NULL;

    int result = parseStatusCode(raw, &status, &next);

    assert(result == 0);
    assert(status == 200);
    assert(next != NULL);
    assert(strncmp(next, "Date: Sun, 09 Jun 2024 12:00:00 GMT\r\n\r\n", 40) == 0);
}

void test_invalid_status(void) {
    const char* raw = "INVALID LINE\r\nContent-Type: text/html\r\n\r\n";
    int status = 0;
    char* next = NULL;

    int result = parseStatusCode(raw, &status, &next);

    assert(result != 0);  // Expect failure
}

int main(void) {
    test_valid_status();
    test_valid_200();
    test_invalid_status();

    printf("All tests passed!\n");
    return 0;
}

