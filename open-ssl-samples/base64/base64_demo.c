#include <string.h>

#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

unsigned char *base64_encode(const unsigned char *input, int length) {
    BIO *b64, *bmem;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    unsigned char *buff = (char *)malloc(bptr->length+1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);

    return buff;
}

char *base64_decode(unsigned char *input, int length)
{
    char *buffer = (char *)malloc(length);
    if (buffer) {
        printf("malloc failed!\n");
        return NULL;
    }
    memset(buffer, 0, length);

    BIO *b64, *bmem;
    b64 = BIO_new(BIO_f_base64());
    /* if donot work, add here: BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); */
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    /* if donot work, change to BIO_push(b64, bmem); */

    BIO_read(bmem, buffer, length);

    BIO_free_all(bmem);

    return buffer;
}

int main(int argc, char **argv) {
    char *str = "hello world!";
    unsigned char *output = NULL;
    unsigned char *decode = NULL;
    printf("Source: '%s'\n", str);

    output = base64_encode(str, strlen(str));
    printf("Base64(encode): *%s*\n", output);
    /* '*' takes no effects when decode the base64 string, means the string can contain '*' */

    decode = output;
    base64_decode2(decode, strlen(decode), &output);
    //output = base64_decode(decode, strlen(decode));
    printf("String(decode): '%s'\n", output);

    free(decode);
    free(output);
}


