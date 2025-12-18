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
            .Capacity = 3,
        };
    case POST:
        return (String){
            .Data = "POST",
            .Size = 4,
            .Capacity = 4,
        };
    case PUT:
        return (String){
            .Data = "PUT",
            .Size = 3,
            .Capacity = 3,
        };
    case DELETE:
        return (String){
            .Data = "DELETE",
            .Size = 6,
            .Capacity = 6,
        };
    case PATCH:
        return (String){
            .Data = "PATCH",
            .Size = 5,
            .Capacity = 5,
        };
    default:
        return (String){
            .Data = NULL,
            .Size = 0,
            .Capacity = 0,
        };
    }
}

String getHttpVersionStr()
{
    return (String){
        .Data = "HTTP/1.1",
        .Size = 8,
        .Capacity = 8,
    };
}

int GenerateHttpReqStr(String* output, List* httpLines)
{
    // Total output length calculation
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
    if (output->Data == NULL)
    {
        return -1;
    }
    output->Capacity = outputLength;

    // output builder iteration
    String iteratedLine = (String){
        .Data = output->Data,
        .Size = 0,
        .Capacity = outputLength,
    };
    currNode = httpLines->Head;
    while (currNode != NULL)
    {
        StringCopy((String*)currNode->Data, &iteratedLine);
        iteratedLine.Data = iteratedLine.Data + iteratedLine.Size;
        iteratedLine.Size = 0;
        StringCopyFromCharPtr(&iteratedLine, CRLF, strlen(CRLF));
        iteratedLine.Data = iteratedLine.Data + iteratedLine.Size;
        iteratedLine.Size = 0;
        currNode = currNode->Next;
    }

    StringCopyFromCharPtr(&iteratedLine, CRLF, strlen(CRLF));
    output->Size = outputLength;
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

    List* httpLines = NewList();
    if (httpLines == NULL)
    {
        return -1;
    }

    size_t httpStartLineCapacity = httpMethod.Size + httpPath->Size + httpVersion.Size + 3;
    String* httpStartLine = NewStringWithCapacity(httpStartLineCapacity);
    if (httpStartLine == NULL)
    {
        return -1;
    }

    // HTTP Startline builder
    String iteratedLine = (String){
        .Data = httpStartLine->Data,
        .Size = 0,
        .Capacity = httpStartLineCapacity,
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
    httpStartLine->Size = strlen(httpStartLine->Data);
    if (ListAdd(httpLines, httpStartLine) != 0)
    {
        FreeString(httpStartLine);
        free(httpStartLine);
        FreeList(httpLines);
        return -1;
    }

    // HTTP Header builder (HOST line)
    size_t httpHostLineCapacity = 4 + 2 + host->Size;
    String* httpHostLine = NewStringWithCapacity(httpHostLineCapacity);
    if (httpHostLine == NULL)
    {
        FreeString(httpStartLine);
        free(httpStartLine);
        FreeList(httpLines);
        return -1;
    }
    iteratedLine = (String){
        .Data = httpHostLine->Data,
        .Size = 0,
        .Capacity = httpHostLineCapacity,
    };
    StringCopyFromCharPtr(&iteratedLine, HOST_KEY, strlen(HOST_KEY));
    iteratedLine.Data = iteratedLine.Data + iteratedLine.Size;
    iteratedLine.Size = 0;
    StringCopy(host, &iteratedLine);
    iteratedLine.Data[iteratedLine.Size] = 0;
    httpHostLine->Size = strlen(httpHostLine->Data);
    if (ListAdd(httpLines, httpHostLine) != 0)
    {
        FreeString(httpStartLine);
        free(httpStartLine);
        FreeString(httpHostLine);
        free(httpHostLine);
        FreeList(httpLines);
        return -1;
    }

    int result = GenerateHttpReqStr(output, httpLines);

    // Clean up
    FreeString(httpStartLine);
    free(httpStartLine);
    FreeString(httpHostLine);
    free(httpHostLine);
    FreeList(httpLines);

    return result;
}

