#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "message_push_request.h"



message_push_request_t *message_push_request_create(
    list_t *actions,
    char *content,
    int needPush,
    char *title
    ) {
	message_push_request_t *message_push_request_local_var = malloc(sizeof(message_push_request_t));
    if (!message_push_request_local_var) {
        return NULL;
    }
	message_push_request_local_var->actions = actions;
	message_push_request_local_var->content = content;
	message_push_request_local_var->needPush = needPush;
	message_push_request_local_var->title = title;

	return message_push_request_local_var;
}


void message_push_request_free(message_push_request_t *message_push_request) {
    listEntry_t *listEntry;
	list_ForEach(listEntry, message_push_request->actions) {
		action_free(listEntry->data);
	}
	list_free(message_push_request->actions);
    free(message_push_request->content);
    free(message_push_request->title);
	free(message_push_request);
}

cJSON *message_push_request_convertToJSON(message_push_request_t *message_push_request) {
	cJSON *item = cJSON_CreateObject();

	// message_push_request->actions
    if(message_push_request->actions) { 
    cJSON *actions = cJSON_AddArrayToObject(item, "actions");
    if(actions == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *actionsListEntry;
    if (message_push_request->actions) {
    list_ForEach(actionsListEntry, message_push_request->actions) {
    cJSON *itemLocal = action_convertToJSON(actionsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(actions, itemLocal);
    }
    }
     } 


	// message_push_request->content
    if (!message_push_request->content) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "content", message_push_request->content) == NULL) {
    goto fail; //String
    }


	// message_push_request->needPush
    if (!message_push_request->needPush) {
        goto fail;
    }
    
    if(cJSON_AddBoolToObject(item, "needPush", message_push_request->needPush) == NULL) {
    goto fail; //Bool
    }


	// message_push_request->title
    if (!message_push_request->title) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "title", message_push_request->title) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	if (item) {
        cJSON_Delete(item);
    }
	return NULL;
}

message_push_request_t *message_push_request_parseFromJSON(cJSON *message_push_requestJSON){

    message_push_request_t *message_push_request_local_var = NULL;

    // message_push_request->actions
    cJSON *actions = cJSON_GetObjectItemCaseSensitive(message_push_requestJSON, "actions");
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

    // message_push_request->content
    cJSON *content = cJSON_GetObjectItemCaseSensitive(message_push_requestJSON, "content");
    if (!content) {
        goto end;
    }

    
    if(!cJSON_IsString(content))
    {
    goto end; //String
    }

    // message_push_request->needPush
    cJSON *needPush = cJSON_GetObjectItemCaseSensitive(message_push_requestJSON, "needPush");
    if (!needPush) {
        goto end;
    }

    
    if(!cJSON_IsBool(needPush))
    {
    goto end; //Bool
    }

    // message_push_request->title
    cJSON *title = cJSON_GetObjectItemCaseSensitive(message_push_requestJSON, "title");
    if (!title) {
        goto end;
    }

    
    if(!cJSON_IsString(title))
    {
    goto end; //String
    }


    message_push_request_local_var = message_push_request_create (
        actions ? actionsList : NULL,
        strdup(content->valuestring),
        needPush->valueint,
        strdup(title->valuestring)
        );

    return message_push_request_local_var;
end:
    return NULL;

}
