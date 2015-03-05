#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s file\n", argv[0]);
        return 1;
    }

    struct stat buf;
    stat(argv[1], &buf);
    printf("mode: %d\n", buf.st_mode);

    return 0;
}
