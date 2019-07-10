/*
 * page_response_of_message_object.h
 *
 * 
 */

#ifndef _page_response_of_message_object_H_
#define _page_response_of_message_object_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "message_object.h"



typedef struct page_response_of_message_object_t {
    list_t *content; //nonprimitive container
    long totalElements; //numeric
    long totalPages; //numeric

} page_response_of_message_object_t;

page_response_of_message_object_t *page_response_of_message_object_create(
    list_t *content,
    long totalElements,
    long totalPages
);

void page_response_of_message_object_free(page_response_of_message_object_t *page_response_of_message_object);

page_response_of_message_object_t *page_response_of_message_object_parseFromJSON(cJSON *page_response_of_message_objectJSON);

cJSON *page_response_of_message_object_convertToJSON(page_response_of_message_object_t *page_response_of_message_object);

#endif /* _page_response_of_message_object_H_ */

