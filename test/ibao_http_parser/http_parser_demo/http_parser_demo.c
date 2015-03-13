#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

void dump(const char *buf, size_t length);

int my_message_begin(http_parser *);
int my_url_callback(http_parser *, const char *buf, size_t length);
int my_status(http_parser *, const char *buf, size_t length);
int my_header_field_callback(http_parser *, const char *buf, size_t length);
int my_header_value(http_parser *, const char *buf, size_t length);
int my_headers_complete(http_parser *);
int my_body(http_parser *, const char *buf, size_t length);
int my_message_complete(http_parser *);

int main(int argc, char **argv) {
    char *raw =  "HTTP/1.1 301 Moved Permanently\r\n"
    "Location: http://www.google.com/\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Date: Sun, 26 Apr 2009 11:11:49 GMT\r\n"
    "Expires: Tue, 26 May 2009 11:11:49 GMT\r\n"
    "X-$PrototypeBI-Version: 1.6.0.3\r\n" /* $ char in header field */
    "Cache-Control: public, max-age=2592000\r\n"
    "Server: gws\r\n"
    "Content-Length:  219  \r\n"
    "\r\n"
    "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\n"
    "<TITLE>301 Moved</TITLE></HEAD><BODY>\n"
    "<H1>301 Moved</H1>\n"
    "The document has moved\n"
    "<A HREF=\"http://www.google.com/\">here</A>.\r\n"
    "</BODY></HTML>\r\n";
    printf("%s\n", raw);

    /*
    struct http_parser_settings {
    http_cb      on_message_begin;
    http_data_cb on_url;
    http_data_cb on_status;
    http_data_cb on_header_field;
    http_data_cb on_header_value;
    http_cb      on_headers_complete;
    http_data_cb on_body;
    http_cb      on_message_complete;
    };
    */
    http_parser_settings settings;
    /* Fill All Callbacks */ 
    settings.on_message_begin = my_message_begin;
    settings.on_url = my_url_callback;
    settings.on_status = my_status;
    settings.on_header_field = my_header_field_callback;
    settings.on_header_value = my_header_value;
    settings.on_headers_complete = my_headers_complete;
    settings.on_body = my_body;
    settings.on_message_complete = my_message_complete;
    /* Note: Less Callback Will Cause Segmentation fault(core dumped) */

     
    http_parser *parser = malloc(sizeof(struct http_parser));
    http_parser_init(parser, HTTP_RESPONSE);

    /* It can be called more than once, The Same Result! */
    /*
    size_t ret = http_parser_execute(parser,
                            &settings,
                            raw,
                            strlen(raw));
    */
    ///*
    size_t ret = http_parser_execute(parser,
                            &settings,
                            raw,
                            strlen(raw) - 10);
           ret = http_parser_execute(parser,
                            &settings,
                            raw + (strlen(raw) - 10),
                            10);
    //*/

    /* Also can make the four param be 0 to End (No Callback)*/
    http_parser_execute(parser, &settings, raw, 0);
        
    printf("parser->status_code [%d]\n", parser->status_code);

    free(parser);
    printf("End\n");
    return 0;
}

int my_message_begin(http_parser *http_parser) {
    printf("****** my_message_begin ******\n");
    return 0;
}

int my_url_callback(http_parser *http_parser, const char *buf, size_t length) {
    printf("my_url\n");
    dump(buf, length);
    return 0;
}

int my_status(http_parser *http_parser, const char *buf, size_t length) {
    printf("[status]\n : ");
    dump(buf, length);
    return 0;
}

/* Field And Value Will Be Called More Than One Time
 *  
 * Field : Value  is of pairs
 *
 * One pair callback one time !
 */
int my_header_field_callback(http_parser *http_parser, const char *buf, size_t length) {
    //printf("my_header_field\n");
    dump(buf, length);
    printf(" : ");
    return 0;
}

int my_header_value(http_parser *http_parser, const char *buf, size_t length) {
    //printf("my_header_value\n");
    dump(buf, length);
    return 0;
}

int my_headers_complete(http_parser *http_parser) {
    printf("*** my_headers_complete ***\n");
    return 0;
}

int my_body(http_parser *http_parser, const char *buf, size_t length) {
    printf("[body]\n");
    printf(" : ");
    dump(buf, length);
    return 0;
}

int my_message_complete(http_parser *http_parser) {
    printf("*** my_message_complete ***\n");
    return 0;
}

void dump(const char *buf, size_t length) {
    /* Need One More For '\0' */
    char str[length + 1];
    snprintf(str, length + 1, "%s", buf);
    // Not snprintf(str, length + 1, "[%ld][%s]", length, buf);
    // It contain the Number!! so str must be Larger !
   
    // We do not need to print length
    printf("[%s]\n", str);
    
}


