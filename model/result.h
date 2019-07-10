/*
 * result.h
 *
 * 
 */

#ifndef _result_H_
#define _result_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "object.h"



typedef struct result_t {
    int code; //numeric
    object_t *data; //object
    char *errmsg; // string

} result_t;

result_t *result_create(
    int code,
    object_t *data,
    char *errmsg
);

void result_free(result_t *result);

result_t *result_parseFromJSON(cJSON *resultJSON);

cJSON *result_convertToJSON(result_t *result);

#endif /* _result_H_ */

