#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "DaDaPushMessageAPI.h"


#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)

// push Message to a Channel
//
// <h2>Rate Limit:</h2><ul><li>1 request per 1s</li><li>30 request per 1m</li><li>500 request per 1h</li></ul><h2>Result code/errmsg List:</h2><ul><li>0: ok</li><li>1: server error</li><li>101: channel is exists</li><li>102: channel is not exists</li><li>103: channel token error</li><li>104: channel is not exists</li><li>105: message is not exists</li><li>204: bad request</li><li>205: permission deny</li><li>206: too many request, please after 5 minutes to try!</li><li>301: duplicate username/email</li><li>302: user is not exists</li><li>303: user password is error</li><li>304: client push token is error</li><li>305: user is disabled</li><li>306: your subscription is expired</li><li>307: user not subscribe channel</li></ul>
//
result_of_message_push_response_t*
DaDaPushMessageAPI_createMessage(apiClient_t *apiClient ,message_push_request_t * body ,char * x_channel_token)
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = list_create();
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = list_create();
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/api/v1/message")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/api/v1/message");




    // header parameters
    char *keyHeader_x_channel_token;
    char * valueHeader_x_channel_token;
    keyValuePair_t *keyPairHeader_x_channel_token = 0;
    if (x_channel_token) {
        keyHeader_x_channel_token = strdup("x_channel_token");
        valueHeader_x_channel_token = strdup((x_channel_token));
        keyPairHeader_x_channel_token = keyValuePair_create(keyHeader_x_channel_token, valueHeader_x_channel_token);
        list_addElement(localVarHeaderParameters,keyPairHeader_x_channel_token);
    }


    // Body Param
    cJSON *localVarSingleItemJSON_body;
    if (body != NULL)
    {
        //string
        localVarSingleItemJSON_body = message_push_request_convertToJSON(body);
        localVarBodyParameters = cJSON_Print(localVarSingleItemJSON_body);
    }
    list_addElement(localVarHeaderType,"application/json"); //produces
    list_addElement(localVarContentType,"application/json"); //consumes
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "POST");

    if (apiClient->response_code == 200) {
        printf("%s\n","OK");
    }
    //nonprimitive not container
    cJSON *DaDaPushMessageAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    result_of_message_push_response_t *elementToReturn = result_of_message_push_response_parseFromJSON(DaDaPushMessageAPIlocalVarJSON);
    cJSON_Delete(DaDaPushMessageAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    list_free(localVarHeaderParameters);
    
    list_free(localVarHeaderType);
    list_free(localVarContentType);
    free(localVarPath);
    free(keyHeader_x_channel_token);
    free(valueHeader_x_channel_token);
    free(keyPairHeader_x_channel_token);
    cJSON_Delete(localVarSingleItemJSON_body);
    free(localVarBodyParameters);
    return elementToReturn;
end:
    return NULL;

}

// delete a Channel Message
//
// <h2>Rate Limit:</h2><ul><li>10 request per 1s</li><li>100 request per 1m</li><li>1000 request per 1h</li></ul><h2>Result code/errmsg List:</h2><ul><li>0: ok</li><li>1: server error</li><li>101: channel is exists</li><li>102: channel is not exists</li><li>103: channel token error</li><li>104: channel is not exists</li><li>105: message is not exists</li><li>204: bad request</li><li>205: permission deny</li><li>206: too many request, please after 5 minutes to try!</li><li>301: duplicate username/email</li><li>302: user is not exists</li><li>303: user password is error</li><li>304: client push token is error</li><li>305: user is disabled</li><li>306: your subscription is expired</li><li>307: user not subscribe channel</li></ul>
//
result_t*
DaDaPushMessageAPI_deleteMessage(apiClient_t *apiClient ,long messageId ,char * x_channel_token)
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = list_create();
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/api/v1/message/{messageId}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/api/v1/message/{messageId}");


    // Path Params
    long sizeOfPathParams_messageId = sizeof(messageId)+3 + strlen("{ messageId }");
    if(messageId == 0){
        goto end;
    }
    char* localVarToReplace_messageId = malloc(sizeOfPathParams_messageId);
    snprintf(localVarToReplace_messageId, sizeOfPathParams_messageId, "{%s}", "messageId");

    char localVarBuff_messageId[256];
    intToStr(localVarBuff_messageId, messageId);

    localVarPath = strReplace(localVarPath, localVarToReplace_messageId, localVarBuff_messageId);




    // header parameters
    char *keyHeader_x_channel_token;
    char * valueHeader_x_channel_token;
    keyValuePair_t *keyPairHeader_x_channel_token = 0;
    if (x_channel_token) {
        keyHeader_x_channel_token = strdup("x_channel_token");
        valueHeader_x_channel_token = strdup((x_channel_token));
        keyPairHeader_x_channel_token = keyValuePair_create(keyHeader_x_channel_token, valueHeader_x_channel_token);
        list_addElement(localVarHeaderParameters,keyPairHeader_x_channel_token);
    }

    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "DELETE");

    if (apiClient->response_code == 200) {
        printf("%s\n","OK");
    }
    //nonprimitive not container
    cJSON *DaDaPushMessageAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    result_t *elementToReturn = result_parseFromJSON(DaDaPushMessageAPIlocalVarJSON);
    cJSON_Delete(DaDaPushMessageAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    list_free(localVarHeaderParameters);
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    free(localVarToReplace_messageId);
    free(keyHeader_x_channel_token);
    free(valueHeader_x_channel_token);
    free(keyPairHeader_x_channel_token);
    return elementToReturn;
end:
    return NULL;

}

// get a Channel Message
//
// <h2>Rate Limit:</h2><ul><li>10 request per 1s</li><li>100 request per 1m</li><li>1000 request per 1h</li></ul><h2>Result code/errmsg List:</h2><ul><li>0: ok</li><li>1: server error</li><li>101: channel is exists</li><li>102: channel is not exists</li><li>103: channel token error</li><li>104: channel is not exists</li><li>105: message is not exists</li><li>204: bad request</li><li>205: permission deny</li><li>206: too many request, please after 5 minutes to try!</li><li>301: duplicate username/email</li><li>302: user is not exists</li><li>303: user password is error</li><li>304: client push token is error</li><li>305: user is disabled</li><li>306: your subscription is expired</li><li>307: user not subscribe channel</li></ul>
//
result_of_message_object_t*
DaDaPushMessageAPI_getMessage(apiClient_t *apiClient ,long messageId ,char * x_channel_token)
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = list_create();
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/api/v1/message/{messageId}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/api/v1/message/{messageId}");


    // Path Params
    long sizeOfPathParams_messageId = sizeof(messageId)+3 + strlen("{ messageId }");
    if(messageId == 0){
        goto end;
    }
    char* localVarToReplace_messageId = malloc(sizeOfPathParams_messageId);
    snprintf(localVarToReplace_messageId, sizeOfPathParams_messageId, "{%s}", "messageId");

    char localVarBuff_messageId[256];
    intToStr(localVarBuff_messageId, messageId);

    localVarPath = strReplace(localVarPath, localVarToReplace_messageId, localVarBuff_messageId);




    // header parameters
    char *keyHeader_x_channel_token;
    char * valueHeader_x_channel_token;
    keyValuePair_t *keyPairHeader_x_channel_token = 0;
    if (x_channel_token) {
        keyHeader_x_channel_token = strdup("x_channel_token");
        valueHeader_x_channel_token = strdup((x_channel_token));
        keyPairHeader_x_channel_token = keyValuePair_create(keyHeader_x_channel_token, valueHeader_x_channel_token);
        list_addElement(localVarHeaderParameters,keyPairHeader_x_channel_token);
    }

    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "GET");

    if (apiClient->response_code == 200) {
        printf("%s\n","OK");
    }
    //nonprimitive not container
    cJSON *DaDaPushMessageAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    result_of_message_object_t *elementToReturn = result_of_message_object_parseFromJSON(DaDaPushMessageAPIlocalVarJSON);
    cJSON_Delete(DaDaPushMessageAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    list_free(localVarHeaderParameters);
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    free(localVarToReplace_messageId);
    free(keyHeader_x_channel_token);
    free(valueHeader_x_channel_token);
    free(keyPairHeader_x_channel_token);
    return elementToReturn;
end:
    return NULL;

}

// get Message List
//
// <h2>Rate Limit:</h2><ul><li>1 request per 1s</li><li>45 request per 1m</li></ul><h2>Result code/errmsg List:</h2><ul><li>0: ok</li><li>1: server error</li><li>101: channel is exists</li><li>102: channel is not exists</li><li>103: channel token error</li><li>104: channel is not exists</li><li>105: message is not exists</li><li>204: bad request</li><li>205: permission deny</li><li>206: too many request, please after 5 minutes to try!</li><li>301: duplicate username/email</li><li>302: user is not exists</li><li>303: user password is error</li><li>304: client push token is error</li><li>305: user is disabled</li><li>306: your subscription is expired</li><li>307: user not subscribe channel</li></ul>
//
result_of_page_response_of_message_object_t*
DaDaPushMessageAPI_getMessages(apiClient_t *apiClient ,int page ,int pageSize ,char * x_channel_token)
{
    list_t    *localVarQueryParameters = list_create();
    list_t    *localVarHeaderParameters = list_create();
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/api/v1/messages")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/api/v1/messages");




    // header parameters
    char *keyHeader_x_channel_token;
    char * valueHeader_x_channel_token;
    keyValuePair_t *keyPairHeader_x_channel_token = 0;
    if (x_channel_token) {
        keyHeader_x_channel_token = strdup("x_channel_token");
        valueHeader_x_channel_token = strdup((x_channel_token));
        keyPairHeader_x_channel_token = keyValuePair_create(keyHeader_x_channel_token, valueHeader_x_channel_token);
        list_addElement(localVarHeaderParameters,keyPairHeader_x_channel_token);
    }


    // query parameters
    char *keyQuery_page;
    int valueQuery_page;
    keyValuePair_t *keyPairQuery_page = 0;
    if (page)
    {
        keyQuery_page = strdup("page");
        valueQuery_page = (page);
        keyPairQuery_page = keyValuePair_create(keyQuery_page, &valueQuery_page);
        list_addElement(localVarQueryParameters,keyPairQuery_page);
    }

    // query parameters
    char *keyQuery_pageSize;
    int valueQuery_pageSize;
    keyValuePair_t *keyPairQuery_pageSize = 0;
    if (pageSize)
    {
        keyQuery_pageSize = strdup("pageSize");
        valueQuery_pageSize = (pageSize);
        keyPairQuery_pageSize = keyValuePair_create(keyQuery_pageSize, &valueQuery_pageSize);
        list_addElement(localVarQueryParameters,keyPairQuery_pageSize);
    }
    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "GET");

    if (apiClient->response_code == 200) {
        printf("%s\n","OK");
    }
    //nonprimitive not container
    cJSON *DaDaPushMessageAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    result_of_page_response_of_message_object_t *elementToReturn = result_of_page_response_of_message_object_parseFromJSON(DaDaPushMessageAPIlocalVarJSON);
    cJSON_Delete(DaDaPushMessageAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    list_free(localVarQueryParameters);
    list_free(localVarHeaderParameters);
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    free(keyHeader_x_channel_token);
    free(valueHeader_x_channel_token);
    free(keyPairHeader_x_channel_token);
    free(keyQuery_page);
    keyValuePair_free(keyPairQuery_page);
    free(keyQuery_pageSize);
    keyValuePair_free(keyPairQuery_pageSize);
    return elementToReturn;
end:
    return NULL;

}

