#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "message_object.h"



message_object_t *message_object_create(
    list_t *actions,
    char *channelName,
    char *content,
    char *createdAt,
    long id,
    char *title
    ) {
	message_object_t *message_object_local_var = malloc(sizeof(message_object_t));
    if (!message_object_local_var) {
        return NULL;
    }
	message_object_local_var->actions = actions;
	message_object_local_var->channelName = channelName;
	message_object_local_var->content = content;
	message_object_local_var->createdAt = createdAt;
	message_object_local_var->id = id;
	message_object_local_var->title = title;

	return message_object_local_var;
}


void message_object_free(message_object_t *message_object) {
    listEntry_t *listEntry;
	list_ForEach(listEntry, message_object->actions) {
		action_free(listEntry->data);
	}
	list_free(message_object->actions);
    free(message_object->channelName);
    free(message_object->content);
    free(message_object->createdAt);
    free(message_object->title);
	free(message_object);
}

cJSON *message_object_convertToJSON(message_object_t *message_object) {
	cJSON *item = cJSON_CreateObject();

	// message_object->actions
    if(message_object->actions) { 
    cJSON *actions = cJSON_AddArrayToObject(item, "actions");
    if(actions == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *actionsListEntry;
    if (message_object->actions) {
    list_ForEach(actionsListEntry, message_object->actions) {
    cJSON *itemLocal = action_convertToJSON(actionsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(actions, itemLocal);
    }
    }
     } 


	// message_object->channelName
    if (!message_object->channelName) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "channelName", message_object->channelName) == NULL) {
    goto fail; //String
    }


	// message_object->content
    if (!message_object->content) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "content", message_object->content) == NULL) {
    goto fail; //String
    }


	// message_object->createdAt
    if (!message_object->createdAt) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "createdAt", message_object->createdAt) == NULL) {
    goto fail; //String
    }


	// message_object->id
    if (!message_object->id) {
        goto fail;
    }
    
    if(cJSON_AddNumberToObject(item, "id", message_object->id) == NULL) {
    goto fail; //Numeric
    }


	// message_object->title
    if (!message_object->title) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "title", message_object->title) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	if (item) {
        cJSON_Delete(item);
    }
	return NULL;
}

message_object_t *message_object_parseFromJSON(cJSON *message_objectJSON){

    message_object_t *message_object_local_var = NULL;

    // message_object->actions
    cJSON *actions = cJSON_GetObjectItemCaseSensitive(message_objectJSON, "actions");
    list_t *actionsList;
    if (actions) { 
    cJSON *actions_local_nonprimitive;
    if(!cJSON_IsArray(actions)){
        goto end; //nonprimitive container
    }

    actionsList = list_create();

    cJSON_ArrayForEach(actions_local_nonprimitive,actions )
    {
        if(!cJSON_IsObject(actions_local_nonprimitive)){
            goto end;
        }
        action_t *actionsItem = action_parseFromJSON(actions_local_nonprimitive);

        list_addElement(actionsList, actionsItem);
    }
    }

    // message_object->channelName
    cJSON *channelName = cJSON_GetObjectItemCaseSensitive(message_objectJSON, "channelName");
    if (!channelName) {
        goto end;
    }

    
    if(!cJSON_IsString(channelName))
    {
    goto end; //String
    }

    // message_object->content
    cJSON *content = cJSON_GetObjectItemCaseSensitive(message_objectJSON, "content");
    if (!content) {
        goto end;
    }

    
    if(!cJSON_IsString(content))
    {
    goto end; //String
    }

    // message_object->createdAt
    cJSON *createdAt = cJSON_GetObjectItemCaseSensitive(message_objectJSON, "createdAt");
    if (!createdAt) {
        goto end;
    }

    
    if(!cJSON_IsString(createdAt))
    {
    goto end; //String
    }

    // message_object->id
    cJSON *id = cJSON_GetObjectItemCaseSensitive(message_objectJSON, "id");
    if (!id) {
        goto end;
    }

    
    if(!cJSON_IsNumber(id))
    {
    goto end; //Numeric
    }

    // message_object->title
    cJSON *title = cJSON_GetObjectItemCaseSensitive(message_objectJSON, "title");
    if (!title) {
        goto end;
    }

    
    if(!cJSON_IsString(title))
    {
    goto end; //String
    }


    message_object_local_var = message_object_create (
        actions ? actionsList : NULL,
        strdup(channelName->valuestring),
        strdup(content->valuestring),
        strdup(createdAt->valuestring),
        id->valuedouble,
        strdup(title->valuestring)
        );

    return message_object_local_var;
end:
    return NULL;

}
