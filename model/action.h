/*
 * action.h
 *
 * 
 */

#ifndef _action_H_
#define _action_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"

                typedef enum  {  link } type_e;

        char* type_ToString(type_e type);

        type_e type_FromString(char* type);


typedef struct action_t {
    char *name; // string
    type_e type; //enum
    char *url; // string

} action_t;

action_t *action_create(
    char *name,
    type_e type,
    char *url
);

void action_free(action_t *action);

action_t *action_parseFromJSON(cJSON *actionJSON);

cJSON *action_convertToJSON(action_t *action);

#endif /* _action_H_ */

