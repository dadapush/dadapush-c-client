#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "result_of_message_push_response.h"



result_of_message_push_response_t *result_of_message_push_response_create(
    int code,
    message_push_response_t *data,
    char *errmsg
    ) {
	result_of_message_push_response_t *result_of_message_push_response_local_var = malloc(sizeof(result_of_message_push_response_t));
    if (!result_of_message_push_response_local_var) {
        return NULL;
    }
	result_of_message_push_response_local_var->code = code;
	result_of_message_push_response_local_var->data = data;
	result_of_message_push_response_local_var->errmsg = errmsg;

	return result_of_message_push_response_local_var;
}


void result_of_message_push_response_free(result_of_message_push_response_t *result_of_message_push_response) {
    listEntry_t *listEntry;
    message_push_response_free(result_of_message_push_response->data);
    free(result_of_message_push_response->errmsg);
	free(result_of_message_push_response);
}

cJSON *result_of_message_push_response_convertToJSON(result_of_message_push_response_t *result_of_message_push_response) {
	cJSON *item = cJSON_CreateObject();

	// result_of_message_push_response->code
    if (!result_of_message_push_response->code) {
        goto fail;
    }
    
    if(cJSON_AddNumberToObject(item, "code", result_of_message_push_response->code) == NULL) {
    goto fail; //Numeric
    }


	// result_of_message_push_response->data
    if(result_of_message_push_response->data) { 
    cJSON *data_local_JSON = message_push_response_convertToJSON(result_of_message_push_response->data);
    if(data_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "data", data_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


	// result_of_message_push_response->errmsg
    if (!result_of_message_push_response->errmsg) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "errmsg", result_of_message_push_response->errmsg) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	if (item) {
        cJSON_Delete(item);
    }
	return NULL;
}

result_of_message_push_response_t *result_of_message_push_response_parseFromJSON(cJSON *result_of_message_push_responseJSON){

    result_of_message_push_response_t *result_of_message_push_response_local_var = NULL;

    // result_of_message_push_response->code
    cJSON *code = cJSON_GetObjectItemCaseSensitive(result_of_message_push_responseJSON, "code");
    if (!code) {
        goto end;
    }

    
    if(!cJSON_IsNumber(code))
    {
    goto end; //Numeric
    }

    // result_of_message_push_response->data
    cJSON *data = cJSON_GetObjectItemCaseSensitive(result_of_message_push_responseJSON, "data");
    message_push_response_t *data_local_nonprim = NULL;
    if (data) { 
    data_local_nonprim = message_push_response_parseFromJSON(data); //nonprimitive
    }

    // result_of_message_push_response->errmsg
    cJSON *errmsg = cJSON_GetObjectItemCaseSensitive(result_of_message_push_responseJSON, "errmsg");
    if (!errmsg) {
        goto end;
    }

    
    if(!cJSON_IsString(errmsg))
    {
    goto end; //String
    }


    result_of_message_push_response_local_var = result_of_message_push_response_create (
        code->valuedouble,
        data ? data_local_nonprim : NULL,
        strdup(errmsg->valuestring)
        );

    return result_of_message_push_response_local_var;
end:
    return NULL;

}
