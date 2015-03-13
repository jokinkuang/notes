#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_LEN (10240)
char G_buf[BUF_LEN];

enum methods{
    GET,
    POST
};

static int __send_request_to_server(const char *ip, const char *port, const char *request, char *resp_buf, ssize_t resp_buf_len) {
    int port_ = atoi(port);
    if (port_ == 0) {
        printf("Port is Unavailable\n"); 
        return -1;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("Socket Create Fail"); 
        return -1;
    }

    struct sockaddr_in s_sock;
    memset(&s_sock, 0, sizeof(s_sock));
    s_sock.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &s_sock.sin_addr); 
    s_sock.sin_port = htons(port_);

    if (connect(fd, (struct sockaddr *)&s_sock, sizeof(s_sock)) < 0) {
        perror("Connect Fail"); 
        goto FAIL;
    }

    ssize_t len = write(fd, request, strlen(request));     
    if (len != strlen(request)) {
        perror("Socket Write Fail"); 
        goto FAIL;
    }

    memset(resp_buf, 0, resp_buf_len);
    len = read(fd, resp_buf, resp_buf_len);
    if (len < 0) {
        perror("Socket Read Fail"); 
        goto FAIL;
    } else if (len == 0) {
        printf("Server Disconnect\n"); 
        goto FAIL;
    } 

    close(fd);
    return 0;
FAIL:
    close(fd);
    return -1;
}

static char * __create_request_string(int method, const char *ip, const char *port, const char *url, const char *data) {

    const char *middle = ""
        // Need GET/POST
        "User-Agent: curl/7.22.0 (x86_64-pc-linux-gnu) libcurl/7.22.0 OpenSSL/1.0.1 zlib/1.2.3.4 libidn/1.23 librtmp/2.3\r\n"
        "Accept: */*\r\n"
        "Content-Type: application/json\r\n";
        // Need Host
        // Need Content-length
        // Need "\r\n"
        // Need Data
    const char *http_ver = "HTTP/1.1";
    switch (method) {
    case GET:
        {           // GCC: In swich case, the variables must be contained in {}  
        //head
        int len = strlen(url) + strlen("GET") + strlen(http_ver);
        char head[len + 5]; // two spaces "\r\n" and '\0'
        sprintf(head, "%s %s %s\r\n\0", "GET", url, http_ver);
        
        //host
        len = strlen("Host") + strlen(ip) + strlen(port);
        char host_[len + 6]; // two : space \r\n and '\0';
        sprintf(host_, "%s: %s:%s\r\n\0", "Host", ip, port);

        // No Need Content-Length
        // Need "\r\n"
        // No Need Data
        
        //package
        len = strlen(head) + strlen(middle) + strlen(host_); 
        //char package[len + 3]; // \r\n  and '\0'
        char *package = malloc(sizeof(char) * (len + 3));
        if (package == NULL) {
            printf("malloc fail\n"); 
            return NULL;
        }
        sprintf(package, "%s%s%s\r\n\0", head, middle, host_);
        //printf("%s\n", package);
        
        return package;
        }

    case POST:
        {           // GCC: In swich case, the variables must be contained in {}  
        //head
        int len = strlen(url) + strlen("POST") + strlen(http_ver);
        char head[len + 5]; // two spaces "\r\n" and '\0'
        sprintf(head, "%s %s %s\r\n\0", "POST", url, http_ver);
        
        //host
        len = strlen("Host") + strlen(ip) + strlen(port);
        char host_[len + 6]; // two : space \r\n and '\0';
        sprintf(host_, "%s: %s:%s\r\n\0", "Host", ip, port);

        //content-length
        len = strlen("Content-Length");
        char content_length[len + 5 + 8];  // : space [max_num_len] \r\n and '\0'
        sprintf(content_length, "%s: %ld\r\n\0", "Content-Length", strlen(data));

        //package
        len = strlen(head) + strlen(middle) + strlen(host_) + strlen(content_length) + strlen(data);
        //char package[len + 3]; // \r\n  and '\0'
        char *package = malloc(sizeof(char) * (len + 3));
        if (package == NULL) {
            printf("malloc fail\n"); 
            return NULL;
        }
        sprintf(package, "%s%s%s%s\r\n%s\0", head, middle, host_, content_length, data);
        //printf("%s\n", package);
        
        return package;
        }
    default:
        return NULL;
    }
}

void do_http_request(int method, const char *ip, const char *port, const char *url, const char *data) {
    
    // Create The Http Request Package. Must Be Freed After Used !
    char *request = __create_request_string(method, ip, port, url, data);
    if (request == NULL) {
        printf("Unavailalbe Request Method\n"); 
        return;
    }
    printf("\n>>\nRequest Pkg [len = %ld]:\n%s", strlen(request), request);

    // (ip, port, request_package, response_package_buffer, buufer_len)
    int ret = __send_request_to_server(ip, port, request, G_buf, BUF_LEN);
    if (ret < 0) {
        printf("Request Fail\n"); 
        return;
    }

    // Free the Http Request Package
    free(request);

    printf("\n<<\nResponse Pkg:\n%s", G_buf);

}

int main(int argc, char **argv) {
    char *ip = "172.26.10.19";
    char *port = "8080";
    char url[256];
    char data[2048];

    //Get "www.baidu.com:80/s?wd=123456789"
    strcpy(url, "/s?wd=123456789");
    do_http_request(GET, "115.239.210.27", "80", url, "");

    strcpy(url, "/guardian/api/gitone/1/register!deviceRegisterRequest.action");
    strcpy(data, "{\"phone\":\"15914330102\",\"serial\":\"se123456\"}");
    do_http_request(POST, ip, port, url, data);

    strcpy(url, "/api/gitone/1/register/request");
    strcpy(data, "{\"phone\":\"15914330102\",\"serial\":\"se123456\"}");
    do_http_request(POST, ip, port, url, data);

    return 0;
}

/* PS Data

    char *get_request = ""
    "POST /guardian/api/gitone/1/register!deviceRegisterRequest.action HTTP/1.1\r\n"
    "User-Agent: curl/7.22.0 (x86_64-pc-linux-gnu) libcurl/7.22.0 OpenSSL/1.0.1 zlib/1.2.3.4 libidn/1.23 librtmp/2.3\r\n"
    "Accept: *//*\r\n"
    "Host: 172.26.10.19:8080\r\n"       //Must Have
    "Content-Type: application/json\r\n"
    "Content-Length: 42\r\n"
    "\r\n"
    "{\"phone\":\"15914330101\",\"serial\":\"se12345\"}";

*/
