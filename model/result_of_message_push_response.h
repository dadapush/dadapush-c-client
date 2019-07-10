/*
 * result_of_message_push_response.h
 *
 * 
 */

#ifndef _result_of_message_push_response_H_
#define _result_of_message_push_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "message_push_response.h"



typedef struct result_of_message_push_response_t {
    int code; //numeric
    message_push_response_t *data; //model
    char *errmsg; // string

} result_of_message_push_response_t;

result_of_message_push_response_t *result_of_message_push_response_create(
    int code,
    message_push_response_t *data,
    char *errmsg
);

void result_of_message_push_response_free(result_of_message_push_response_t *result_of_message_push_response);

result_of_message_push_response_t *result_of_message_push_response_parseFromJSON(cJSON *result_of_message_push_responseJSON);

cJSON *result_of_message_push_response_convertToJSON(result_of_message_push_response_t *result_of_message_push_response);

#endif /* _result_of_message_push_response_H_ */

