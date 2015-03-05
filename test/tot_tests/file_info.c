#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>

/** <time.h> have to be include, or the Source can go through compile, but can not run through!
 * Eg, while not include <time.h>, "%D %T" the %T would get a wrong hour value and others are right.
 **/
char *get_date(time_t t) {
    static char date[] = "2014-12-12 12:12:12";
    struct tm *lt;
    t = time(NULL);
    ctime_r(&t, &date);
    localtime_r(&t, &lt);
    //gmtime_r(&t, &lt);
    printf("date: %s\n", date);
    char timbuf[180];
    strftime(timbuf, sizeof(timbuf), "%D %T", &lt);
    printf("timbuf: %s\n", timbuf);

    time_t tt = time(NULL);
    //产生"YYYY-MM-DD hh:mm:ss"格式的字符串。
    char str[32];
    strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S", localtime(&tt));
    printf("Time: %s\n", str);
    
    return timbuf;
    //snprintf(date, sizeof(date)/sizeof(date[0]), "%d-%d-%d");
#if 0
    struct tm *tm;
    char buf[200];
    /* convert time_t to broken-down time representation */
    tm = localtime(&t);
    /* format time days.month.year hour:minute:seconds */
    strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", tm);
    printf("%s\n", buf);
#endif
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s file\n", argv[0]);
        return 1;
    }

    struct stat buf;
    stat(argv[1], &buf);
    printf("mode: %d\n", buf.st_mode);
    printf("atime:%u | %s\n", buf.st_atime, get_date(buf.st_atime));
    printf("mtime:%u | %s\n", buf.st_mtime, get_date(buf.st_mtime));
    printf("ctime:%u | %s\n", buf.st_ctime, get_date(buf.st_ctime));
//    printf("atime: %u %s\n", buf.st_atime, asctime(localtime(&buf.st_atime)));
//    printf("mtime: %u %s\n", buf.st_mtime, ctime(&buf.st_mtime), "b");
//    printf("ctime: %u %s\n", buf.st_ctime, ctime(&buf.st_ctime), "c");

    return 0;
}
