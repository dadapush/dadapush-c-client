#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "result_of_message_object.h"



result_of_message_object_t *result_of_message_object_create(
    int code,
    message_object_t *data,
    char *errmsg
    ) {
	result_of_message_object_t *result_of_message_object_local_var = malloc(sizeof(result_of_message_object_t));
    if (!result_of_message_object_local_var) {
        return NULL;
    }
	result_of_message_object_local_var->code = code;
	result_of_message_object_local_var->data = data;
	result_of_message_object_local_var->errmsg = errmsg;

	return result_of_message_object_local_var;
}


void result_of_message_object_free(result_of_message_object_t *result_of_message_object) {
    listEntry_t *listEntry;
    message_object_free(result_of_message_object->data);
    free(result_of_message_object->errmsg);
	free(result_of_message_object);
}

cJSON *result_of_message_object_convertToJSON(result_of_message_object_t *result_of_message_object) {
	cJSON *item = cJSON_CreateObject();

	// result_of_message_object->code
    if (!result_of_message_object->code) {
        goto fail;
    }
    
    if(cJSON_AddNumberToObject(item, "code", result_of_message_object->code) == NULL) {
    goto fail; //Numeric
    }


	// result_of_message_object->data
    if(result_of_message_object->data) { 
    cJSON *data_local_JSON = message_object_convertToJSON(result_of_message_object->data);
    if(data_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "data", data_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


	// result_of_message_object->errmsg
    if (!result_of_message_object->errmsg) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "errmsg", result_of_message_object->errmsg) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	if (item) {
        cJSON_Delete(item);
    }
	return NULL;
}

result_of_message_object_t *result_of_message_object_parseFromJSON(cJSON *result_of_message_objectJSON){

    result_of_message_object_t *result_of_message_object_local_var = NULL;

    // result_of_message_object->code
    cJSON *code = cJSON_GetObjectItemCaseSensitive(result_of_message_objectJSON, "code");
    if (!code) {
        goto end;
    }

    
    if(!cJSON_IsNumber(code))
    {
    goto end; //Numeric
    }

    // result_of_message_object->data
    cJSON *data = cJSON_GetObjectItemCaseSensitive(result_of_message_objectJSON, "data");
    message_object_t *data_local_nonprim = NULL;
    if (data) { 
    data_local_nonprim = message_object_parseFromJSON(data); //nonprimitive
    }

    // result_of_message_object->errmsg
    cJSON *errmsg = cJSON_GetObjectItemCaseSensitive(result_of_message_objectJSON, "errmsg");
    if (!errmsg) {
        goto end;
    }

    
    if(!cJSON_IsString(errmsg))
    {
    goto end; //String
    }


    result_of_message_object_local_var = result_of_message_object_create (
        code->valuedouble,
        data ? data_local_nonprim : NULL,
        strdup(errmsg->valuestring)
        );

    return result_of_message_object_local_var;
end:
    return NULL;

}
