#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "message_push_response.h"



message_push_response_t *message_push_response_create(
    long messageId
    ) {
	message_push_response_t *message_push_response_local_var = malloc(sizeof(message_push_response_t));
    if (!message_push_response_local_var) {
        return NULL;
    }
	message_push_response_local_var->messageId = messageId;

	return message_push_response_local_var;
}


void message_push_response_free(message_push_response_t *message_push_response) {
    listEntry_t *listEntry;
	free(message_push_response);
}

cJSON *message_push_response_convertToJSON(message_push_response_t *message_push_response) {
	cJSON *item = cJSON_CreateObject();

	// message_push_response->messageId
    if (!message_push_response->messageId) {
        goto fail;
    }
    
    if(cJSON_AddNumberToObject(item, "messageId", message_push_response->messageId) == NULL) {
    goto fail; //Numeric
    }

	return item;
fail:
	if (item) {
        cJSON_Delete(item);
    }
	return NULL;
}

message_push_response_t *message_push_response_parseFromJSON(cJSON *message_push_responseJSON){

    message_push_response_t *message_push_response_local_var = NULL;

    // message_push_response->messageId
    cJSON *messageId = cJSON_GetObjectItemCaseSensitive(message_push_responseJSON, "messageId");
    if (!messageId) {
        goto end;
    }

    
    if(!cJSON_IsNumber(messageId))
    {
    goto end; //Numeric
    }


    message_push_response_local_var = message_push_response_create (
        messageId->valuedouble
        );

    return message_push_response_local_var;
end:
    return NULL;

}
