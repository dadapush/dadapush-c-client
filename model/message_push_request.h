/*
 * message_push_request.h
 *
 * 
 */

#ifndef _message_push_request_H_
#define _message_push_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "action.h"



typedef struct message_push_request_t {
    list_t *actions; //nonprimitive container
    char *content; // string
    int needPush; //boolean
    char *title; // string

} message_push_request_t;

message_push_request_t *message_push_request_create(
    list_t *actions,
    char *content,
    int needPush,
    char *title
);

void message_push_request_free(message_push_request_t *message_push_request);

message_push_request_t *message_push_request_parseFromJSON(cJSON *message_push_requestJSON);

cJSON *message_push_request_convertToJSON(message_push_request_t *message_push_request);

#endif /* _message_push_request_H_ */

