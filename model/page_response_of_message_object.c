#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "page_response_of_message_object.h"



page_response_of_message_object_t *page_response_of_message_object_create(
    list_t *content,
    long totalElements,
    long totalPages
    ) {
	page_response_of_message_object_t *page_response_of_message_object_local_var = malloc(sizeof(page_response_of_message_object_t));
    if (!page_response_of_message_object_local_var) {
        return NULL;
    }
	page_response_of_message_object_local_var->content = content;
	page_response_of_message_object_local_var->totalElements = totalElements;
	page_response_of_message_object_local_var->totalPages = totalPages;

	return page_response_of_message_object_local_var;
}


void page_response_of_message_object_free(page_response_of_message_object_t *page_response_of_message_object) {
    listEntry_t *listEntry;
	list_ForEach(listEntry, page_response_of_message_object->content) {
		message_object_free(listEntry->data);
	}
	list_free(page_response_of_message_object->content);
	free(page_response_of_message_object);
}

cJSON *page_response_of_message_object_convertToJSON(page_response_of_message_object_t *page_response_of_message_object) {
	cJSON *item = cJSON_CreateObject();

	// page_response_of_message_object->content
    if(page_response_of_message_object->content) { 
    cJSON *content = cJSON_AddArrayToObject(item, "content");
    if(content == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *contentListEntry;
    if (page_response_of_message_object->content) {
    list_ForEach(contentListEntry, page_response_of_message_object->content) {
    cJSON *itemLocal = message_object_convertToJSON(contentListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(content, itemLocal);
    }
    }
     } 


	// page_response_of_message_object->totalElements
    if(page_response_of_message_object->totalElements) { 
    if(cJSON_AddNumberToObject(item, "totalElements", page_response_of_message_object->totalElements) == NULL) {
    goto fail; //Numeric
    }
     } 


	// page_response_of_message_object->totalPages
    if(page_response_of_message_object->totalPages) { 
    if(cJSON_AddNumberToObject(item, "totalPages", page_response_of_message_object->totalPages) == NULL) {
    goto fail; //Numeric
    }
     } 

	return item;
fail:
	if (item) {
        cJSON_Delete(item);
    }
	return NULL;
}

page_response_of_message_object_t *page_response_of_message_object_parseFromJSON(cJSON *page_response_of_message_objectJSON){

    page_response_of_message_object_t *page_response_of_message_object_local_var = NULL;

    // page_response_of_message_object->content
    cJSON *content = cJSON_GetObjectItemCaseSensitive(page_response_of_message_objectJSON, "content");
    list_t *contentList;
    if (content) { 
    cJSON *content_local_nonprimitive;
    if(!cJSON_IsArray(content)){
        goto end; //nonprimitive container
    }

    contentList = list_create();

    cJSON_ArrayForEach(content_local_nonprimitive,content )
    {
        if(!cJSON_IsObject(content_local_nonprimitive)){
            goto end;
        }
        message_object_t *contentItem = message_object_parseFromJSON(content_local_nonprimitive);

        list_addElement(contentList, contentItem);
    }
    }

    // page_response_of_message_object->totalElements
    cJSON *totalElements = cJSON_GetObjectItemCaseSensitive(page_response_of_message_objectJSON, "totalElements");
    if (totalElements) { 
    if(!cJSON_IsNumber(totalElements))
    {
    goto end; //Numeric
    }
    }

    // page_response_of_message_object->totalPages
    cJSON *totalPages = cJSON_GetObjectItemCaseSensitive(page_response_of_message_objectJSON, "totalPages");
    if (totalPages) { 
    if(!cJSON_IsNumber(totalPages))
    {
    goto end; //Numeric
    }
    }


    page_response_of_message_object_local_var = page_response_of_message_object_create (
        content ? contentList : NULL,
        totalElements ? totalElements->valuedouble : 0,
        totalPages ? totalPages->valuedouble : 0
        );

    return page_response_of_message_object_local_var;
end:
    return NULL;

}
