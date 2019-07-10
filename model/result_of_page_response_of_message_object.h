/*
 * result_of_page_response_of_message_object.h
 *
 * 
 */

#ifndef _result_of_page_response_of_message_object_H_
#define _result_of_page_response_of_message_object_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "page_response_of_message_object.h"



typedef struct result_of_page_response_of_message_object_t {
    int code; //numeric
    page_response_of_message_object_t *data; //model
    char *errmsg; // string

} result_of_page_response_of_message_object_t;

result_of_page_response_of_message_object_t *result_of_page_response_of_message_object_create(
    int code,
    page_response_of_message_object_t *data,
    char *errmsg
);

void result_of_page_response_of_message_object_free(result_of_page_response_of_message_object_t *result_of_page_response_of_message_object);

result_of_page_response_of_message_object_t *result_of_page_response_of_message_object_parseFromJSON(cJSON *result_of_page_response_of_message_objectJSON);

cJSON *result_of_page_response_of_message_object_convertToJSON(result_of_page_response_of_message_object_t *result_of_page_response_of_message_object);

#endif /* _result_of_page_response_of_message_object_H_ */

