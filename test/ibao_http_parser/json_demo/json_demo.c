#include <stdio.h>
#include <string.h>
#include "json.h"

char * get_content_from_file(char *argv1);
void dump(json_value *json_obj);

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s <json_file>\n", argv[0]); 
        exit(1);
    }

    /* buf End With '\0' */
    char *buf = get_content_from_file(argv[1]); 

    printf("json_string:\n%s\n", buf);

    json_value *my_json_value;
    my_json_value = json_parse((json_char *)buf, strlen(buf));
    
    if (!my_json_value) {
        printf("json_value is NULL\n"); 
        exit(1);
    }

    dump(my_json_value);

    json_value_free(my_json_value);
   
    free(buf);    
    return 0;
}

char * get_content_from_file(char *argv1) {
    FILE *fp = fopen(argv1, "rb");
    if (!fp) {
        printf("file open fail!\n"); 
        exit(1);
    }
    fseek(fp, 0L, SEEK_END);
    ssize_t file_len=ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char *buf = calloc(file_len, 1);
    if (!buf) {
        printf("malloc fail\n"); 
        exit(1);
    }

    size_t len = fread(buf, sizeof(char), file_len, fp);
    if (len < 0) {
        printf("fread fail\n"); 
        exit(1);
    }
    if (len < file_len) {
        printf("fread error\n"); 
        exit(1);
    }
    /* End With '\0' */
    buf[len - 1] = '\0';
    
    fclose(fp);
    return buf;
}

void dump(json_value *json_obj) {
    switch (json_obj->type) {
       case (json_none): 
           printf("-- None Json --\n"); 
           break;
       case json_object:
           printf("-- Object --\n");
           printf("length: %d\n", json_obj->u.object.length);
           int size = json_obj->u.object.length;
           int i = 0;
           printf("{\n");
           for (i = 0; i < size; i++) {
                printf("name: %s | value: %p\n", json_obj->u.object.values[i].name, 
                        json_obj->u.object.values[i].value); 

                dump(json_obj->u.object.values[i].value);
           }
           printf("}\n");
           break;
       case json_array:
           printf("-- Array --\n");
           printf("length: %d\n", json_obj->u.array.length);
           size = json_obj->u.array.length;
           i = 0;
           printf("[--\n");
           for (i = 0; i< size; i++) {
                printf("value: %p\n", json_obj->u.array.values[i]); 

                dump(json_obj->u.array.values[i]);
           }
           printf("--]\n");
           break;
       case json_string:
           printf("-- String --\n");
           printf("value: %s\n", json_obj->u.string.ptr);
           break;
       case json_double:
           printf("-- Double --\n");
           printf("value: %lf\n", json_obj->u.dbl);
           break;
       case json_integer:
           printf("-- Integer --\n");
           printf("value: %ld\n", json_obj->u.integer);
           break;
       case json_boolean:
           printf("-- Boolean --\n");
           printf("value: %d\n", json_obj->u.boolean);
           break;
       case json_null:
           printf("-- NULL --\n");
           printf("value is NULL\n");
           break;
       default:
           printf("Convert Fail\n");
           break;

    }
}
