//
// Created by Ivan Wijaya on 15/12/25.
//

#include "Http.h"

#include <stdlib.h>
#include <string.h>

#include "../List.h"


const char* CRLF = "\r\n";
const char* HOST_KEY = "HOST: ";

String getHttpMethodStr(HttpMethod method)
{
    switch (method)
    {
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
            .Data = NULL,
            .Size = 0,
        };
    }
}

String getHttpVersionStr()
{
    return (String){
        .Data = "HTTP/1.1",
        .Size = 8,
    };
}

int GenerateHttpReqStr(String* output, List* httpLines)
{
    Node* currNode = httpLines->Head;
    size_t outputLength = 3;
    while (currNode != NULL)
    {
        String tempData = *(String*)currNode->Data;
        outputLength += tempData.Size;
        outputLength += 2;
        currNode = currNode->Next;
    }

    output->Data = malloc(sizeof(char) * outputLength);
    String iteratedLine = (String){
        .Data = output->Data,
        .Size = 0,
    };
    currNode = httpLines->Head;
    while (currNode != NULL)
    {
        StringCopy(currNode->Data, &iteratedLine);
        iteratedLine.Data = iteratedLine.Data + iteratedLine.Size;
        iteratedLine.Size = 0;
        StringCopy(NewString(CRLF, strlen(CRLF)), &iteratedLine);
        iteratedLine.Data = iteratedLine.Data + iteratedLine.Size;
        iteratedLine.Size = 0;
        currNode = currNode->Next;
    }
    StringCopy(NewString(CRLF, strlen(CRLF)), &iteratedLine);
    return 0;
}

// POST /coffee HTTP/1.1            # start-line CRLF
// Host: localhost:42069            # *( field-line CRLF )
// User-Agent: curl/8.6.0           # *( field-line CRLF )
// Accept: */*                      # *( field-line CRLF )
// Content-Type: application/json   # *( field-line CRLF )
// Content-Length: 22               # *( field-line CRLF )
//                                  # CRLF
// {"flavor":"dark mode"}          # [ message-body ]
int CreateHttpRequest(String* output, HttpMethod method, String* host, String* httpPath)
{
    String httpMethod = getHttpMethodStr(method);
    if (httpMethod.Data == NULL)
    {
        return -1;
    }

    String httpVersion = getHttpVersionStr();
    if (output->Data != NULL)
    {
        FreeString(output);
    }


    size_t httpStartLineCapacity = httpMethod.Size + httpPath->Size + httpVersion.Size + 3;
    String httpStartLine = (String){
        .Data = malloc(sizeof(char) * httpStartLineCapacity),
        .Size = 0,
    };

    String iteratedLine = (String){
        .Data = httpStartLine.Data,
        .Size = httpStartLine.Size,
    };
    StringCopy(&httpMethod, &iteratedLine);
    iteratedLine.Data[iteratedLine.Size] = ' ';
    iteratedLine.Data = iteratedLine.Data + iteratedLine.Size + 1;
    iteratedLine.Size = 0;
    StringCopy(httpPath, &iteratedLine);
    iteratedLine.Data[iteratedLine.Size] = ' ';
    iteratedLine.Data = iteratedLine.Data + iteratedLine.Size + 1;
    iteratedLine.Size = 0;
    StringCopy(&httpVersion, &iteratedLine);
    iteratedLine.Data[iteratedLine.Size] = 0;
    httpStartLine.Size = strlen(httpStartLine.Data);

    List* httpLines = NewList();
    ListAdd(httpLines, &httpStartLine);

    String httpHostLine = (String){
        .Data = malloc(sizeof(char) * (4 + 2 + host->Size)),
        .Size = 0,
    };
    iteratedLine = (String){
        .Data = httpHostLine.Data,
        .Size = httpHostLine.Size,
    };

    StringCopy(NewString(HOST_KEY, strlen(HOST_KEY)), &iteratedLine);
    iteratedLine.Data = iteratedLine.Data + iteratedLine.Size;
    iteratedLine.Size = 0;
    StringCopy(host, &iteratedLine);
    iteratedLine.Data[iteratedLine.Size] = 0;
    httpHostLine.Size = strlen(httpHostLine.Data);
    ListAdd(httpLines, &httpHostLine);

    GenerateHttpReqStr(output, httpLines);
    return 0;
}
