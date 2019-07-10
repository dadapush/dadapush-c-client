#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "action.h"


    char* typeaction_ToString(type_e type){
    char *typeArray[] =  { "link" };
        return typeArray[type];
    }

    type_e typeaction_FromString(char* type){
    int stringToReturn = 0;
    char *typeArray[] =  { "link" };
    size_t sizeofArray = sizeof(typeArray) / sizeof(typeArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(type, typeArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
    }

action_t *action_create(
    char *name,
    type_e type,
    char *url
    ) {
	action_t *action_local_var = malloc(sizeof(action_t));
    if (!action_local_var) {
        return NULL;
    }
	action_local_var->name = name;
	action_local_var->type = type;
	action_local_var->url = url;

	return action_local_var;
}


void action_free(action_t *action) {
    listEntry_t *listEntry;
    free(action->name);
    free(action->url);
	free(action);
}

cJSON *action_convertToJSON(action_t *action) {
	cJSON *item = cJSON_CreateObject();

	// action->name
    if (!action->name) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "name", action->name) == NULL) {
    goto fail; //String
    }


	// action->type
    
    if(cJSON_AddStringToObject(item, "type", typeaction_ToString(action->type)) == NULL)
    {
    goto fail; //Enum
    }


	// action->url
    if (!action->url) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "url", action->url) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	if (item) {
        cJSON_Delete(item);
    }
	return NULL;
}

action_t *action_parseFromJSON(cJSON *actionJSON){

    action_t *action_local_var = NULL;

    // action->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(actionJSON, "name");
    if (!name) {
        goto end;
    }

    
    if(!cJSON_IsString(name))
    {
    goto end; //String
    }

    // action->type
    cJSON *type = cJSON_GetObjectItemCaseSensitive(actionJSON, "type");
    if (!type) {
        goto end;
    }

    type_e typeVariable;
    
    if(!cJSON_IsString(type))
    {
    goto end; //Enum
    }
    typeVariable = typeaction_FromString(type->valuestring);

    // action->url
    cJSON *url = cJSON_GetObjectItemCaseSensitive(actionJSON, "url");
    if (!url) {
        goto end;
    }

    
    if(!cJSON_IsString(url))
    {
    goto end; //String
    }


    action_local_var = action_create (
        strdup(name->valuestring),
        typeVariable,
        strdup(url->valuestring)
        );

    return action_local_var;
end:
    return NULL;

}
