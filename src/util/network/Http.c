//
// Created by Ivan Wijaya on 15/12/25.
//

#include "Http.h"

#include <stdlib.h>
#include <string.h>


String getHttpMethodStr(HttpMethod method) {
    switch (method) {
        case GET:
            return (String){
                .Data = "GET",
                .Size = 3,
            };
        case POST:
            return (String){
                .Data = "POST",
                .Size = 4,
            };
        case PUT:
            return (String){
                .Data = "PUT",
                .Size = 3,
            };
        case DELETE:
            return (String){
                .Data = "DELETE",
                .Size = 6,
            };
        case PATCH:
            return (String){
                .Data = "PATCH",
                .Size = 5,
            };
        default:
            return (String){
                .Data = nullptr,
                .Size = 0,
            };
    }
}

String getHttpVersionStr() {
    return (String){
        .Data = "HTTP/1.1",
        .Size = 8,
    };
}

// POST /coffee HTTP/1.1            # start-line CRLF
// Host: localhost:42069            # *( field-line CRLF )
// User-Agent: curl/8.6.0           # *( field-line CRLF )
// Accept: */*                      # *( field-line CRLF )
// Content-Type: application/json   # *( field-line CRLF )
// Content-Length: 22               # *( field-line CRLF )
//                                  # CRLF
// {"flavor":"dark mode"}          # [ message-body ]
int CreateHttpRequest(String *output, HttpMethod method, String *host, String *httpPath) {
    String httpMethod = getHttpMethodStr(method);
    if (httpMethod.Data == nullptr) {
        return -1;
    }

    String httpVersion = getHttpVersionStr();
    if (output->Data != nullptr) {
        FreeString(output);
    }


    size_t httpStartLineCapacity = httpMethod.Size + httpPath->Size + httpVersion.Size + 3;
    String httpStartLine = (String){
        .Data = malloc(sizeof(char) * httpStartLineCapacity),
        .Size = 0,
    };

    String iteratedStartLine = (String){
        .Data = httpStartLine.Data,
        .Size = httpStartLine.Size,
    };
    StringCopy(&httpMethod, &iteratedStartLine);
    iteratedStartLine.Data[iteratedStartLine.Size] = ' ';
    iteratedStartLine.Data = iteratedStartLine.Data + iteratedStartLine.Size + 1;
    iteratedStartLine.Size = 0;
    StringCopy(httpPath, &iteratedStartLine);
    iteratedStartLine.Data[iteratedStartLine.Size] = ' ';
    iteratedStartLine.Data = iteratedStartLine.Data + iteratedStartLine.Size + 1;
    iteratedStartLine.Size = 0;
    StringCopy(&httpVersion, &iteratedStartLine);
    iteratedStartLine.Data[iteratedStartLine.Size] = 0;


    output->Data = httpStartLine.Data;
    output->Size = strlen(httpStartLine.Data);
    return 0;
}
