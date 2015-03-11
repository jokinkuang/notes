#include <stdio.h>
#include <dirent.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s path\n", argv[0]);
        return 1;
    }

    DIR *dp = opendir(argv[1]);
    if (! dp)
        return -1;

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 ||
                strcmp(dirp->d_name, "..") == 0)
            continue;
        printf("%s\n", dirp->d_name);
    }
    if (closedir(dp) < 0)
        printf("can't close directory\n");
    return 0;
}

