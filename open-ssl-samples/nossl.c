#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/err.h"

#include "stdio.h"
#include "string.h"

int main()
{
    BIO * bio;
    int p;

    char * request = "GET / HTTP/1.1\x0D\x0AHost: www.verisign.com\x0D\x0A\x43onnection: Close\x0D\x0A\x0D\x0A";
    char r[1024];

    /* Set up the library */

    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    /* Create and setup the connection */

    bio = BIO_new_connect("www.verisign.com:80");
    if(bio == NULL) { printf("BIO is null\n"); return; }

    if(BIO_do_connect(bio) <= 0)
    {
        ERR_print_errors_fp(stderr);
        BIO_free_all(bio);
        return;
    }

    /* Send the request */

    BIO_write(bio, request, strlen(request));

    /* Read in the response */

    for(;;)
    {
        p = BIO_read(bio, r, 1023);
        if(p <= 0) break;
        r[p] = 0;
        printf("%s", r);
    }

    /* Close the connection and free the context */

    BIO_free_all(bio);
    return 0;
}
