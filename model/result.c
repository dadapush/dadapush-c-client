#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "result.h"



result_t *result_create(
    int code,
    object_t *data,
    char *errmsg
    ) {
	result_t *result_local_var = malloc(sizeof(result_t));
    if (!result_local_var) {
        return NULL;
    }
	result_local_var->code = code;
	result_local_var->data = data;
	result_local_var->errmsg = errmsg;

	return result_local_var;
}


void result_free(result_t *result) {
    listEntry_t *listEntry;
    object_free(result->data);
    free(result->errmsg);
	free(result);
}

cJSON *result_convertToJSON(result_t *result) {
	cJSON *item = cJSON_CreateObject();

	// result->code
    if (!result->code) {
        goto fail;
    }
    
    if(cJSON_AddNumberToObject(item, "code", result->code) == NULL) {
    goto fail; //Numeric
    }


	// result->data
    if(result->data) { 
    cJSON *data_object = object_convertToJSON(result->data);
    if(data_object == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "data", data_object);
    if(item->child == NULL) {
    goto fail;
    }
     } 


	// result->errmsg
    if (!result->errmsg) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "errmsg", result->errmsg) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	if (item) {
        cJSON_Delete(item);
    }
	return NULL;
}

result_t *result_parseFromJSON(cJSON *resultJSON){

    result_t *result_local_var = NULL;

    // result->code
    cJSON *code = cJSON_GetObjectItemCaseSensitive(resultJSON, "code");
    if (!code) {
        goto end;
    }

    
    if(!cJSON_IsNumber(code))
    {
    goto end; //Numeric
    }

    // result->data
    cJSON *data = cJSON_GetObjectItemCaseSensitive(resultJSON, "data");
    object_t *data_local_object = NULL;
    if (data) { 
    data_local_object = object_parseFromJSON(data); //object
    }

    // result->errmsg
    cJSON *errmsg = cJSON_GetObjectItemCaseSensitive(resultJSON, "errmsg");
    if (!errmsg) {
        goto end;
    }

    
    if(!cJSON_IsString(errmsg))
    {
    goto end; //String
    }


    result_local_var = result_create (
        code->valuedouble,
        data ? data_local_object : NULL,
        strdup(errmsg->valuestring)
        );

    return result_local_var;
end:
    return NULL;

}
