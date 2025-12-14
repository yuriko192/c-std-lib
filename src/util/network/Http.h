//
// Created by Ivan Wijaya on 15/12/25.
//

#ifndef CSTDLIB_HTTP_H
#define CSTDLIB_HTTP_H

#include "../String.h"

typedef enum HTTP_METHOD {
    GET, POST, PUT, DELETE, PATCH
} HttpMethod;


int CreateHttpRequest(String *output, HttpMethod method, String *host, String *httpPath);

#endif //CSTDLIB_HTTP_H
