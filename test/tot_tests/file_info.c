#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>

const char *get_date(time_t t) {
    static char date[] = "2014-12-12 12:12:12";
    localtime_r(&t, &lt);
    char timbuf[80];
    strftime(timbuf, sizeof(timbuf), "%c", &lt);
    snprintf(date, sizeof(date)/sizeof(date[0]), "%d-%d-%d");

    struct tm *tm;
    char buf[200];
    /* convert time_t to broken-down time representation */
    tm = localtime(&t);
    /* format time days.month.year hour:minute:seconds */
    strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", tm);
    printf("%s\n", buf);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s file\n", argv[0]);
        return 1;
    }

    struct stat buf;
    stat(argv[1], &buf);
    printf("mode: %d\n", buf.st_mode);
    printf("atime: %u %s\n", buf.st_atime, asctime(localtime(&buf.st_atime)));
//    printf("mtime: %u %s\n", buf.st_mtime, ctime(&buf.st_mtime), "b");
//    printf("ctime: %u %s\n", buf.st_ctime, ctime(&buf.st_ctime), "c");

    return 0;
}
