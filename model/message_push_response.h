/*
 * message_push_response.h
 *
 * 
 */

#ifndef _message_push_response_H_
#define _message_push_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"



typedef struct message_push_response_t {
    long messageId; //numeric

} message_push_response_t;

message_push_response_t *message_push_response_create(
    long messageId
);

void message_push_response_free(message_push_response_t *message_push_response);

message_push_response_t *message_push_response_parseFromJSON(cJSON *message_push_responseJSON);

cJSON *message_push_response_convertToJSON(message_push_response_t *message_push_response);

#endif /* _message_push_response_H_ */

