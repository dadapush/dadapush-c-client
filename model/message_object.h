/*
 * message_object.h
 *
 * 
 */

#ifndef _message_object_H_
#define _message_object_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "action.h"



typedef struct message_object_t {
    list_t *actions; //nonprimitive container
    char *channelName; // string
    char *content; // string
    char *createdAt; // string
    long id; //numeric
    char *title; // string

} message_object_t;

message_object_t *message_object_create(
    list_t *actions,
    char *channelName,
    char *content,
    char *createdAt,
    long id,
    char *title
);

void message_object_free(message_object_t *message_object);

message_object_t *message_object_parseFromJSON(cJSON *message_objectJSON);

cJSON *message_object_convertToJSON(message_object_t *message_object);

#endif /* _message_object_H_ */

