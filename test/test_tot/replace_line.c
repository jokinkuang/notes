/*
 * C Program to Replace a specified Line in a Text File
 */
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s file\n", argv[0]);
        return 1;
    }

    FILE *srcfp, *dstfp;
    char *srcfile;
    char c;
    int delete_line, line = 1;

    srcfile = argv[1];
    printf("file name: %s\n", srcfile);

    srcfp = fopen(srcfile, "r");

    //print the contents of file.
    printf("%d ", line);
    c = getc(srcfp);
    while (c != EOF) {
        if (c == '\n')
            printf("\n%d ", ++line);
        else 
            printf("%c", c);
        c = getc(srcfp);
    }

    printf("\nEnter line number to be deleted and replaced:");
    scanf("%d", &delete_line);

    //take srcfp to start point.
    rewind(srcfp);

    //open result in write mode
    dstfp = fopen("replace.result", "w");

    line = 1;
    printf("%d ", line);
    c = getc(srcfp);
    while (c != EOF) {
        if (line == delete_line) {
            while (c != '\n') {
                printf("%c", c);
                c = getc(srcfp);
            }
            /* get a '\n' means the line end */
            printf("Enter new text:");
            fflush(stdin);
            fflush(stdin);
            printf("====%c====\n", getchar());
            while ((c = getchar()) != '\n')
                putc(c, dstfp);
            printf("\n");
            fputs("\n", dstfp);
            line++;
        } else if (c == '\n') {
            printf("\n%d ", ++line);
        } else {
            printf("%c", c);
#if 0
            //till the line to be deleted comes,copy the content to other
            if (line != delete_line) {
                putc(c, dstfp);
            }
            else {
                while ((c = getc(srcfp)) != '\n') {
                }
                //read and skip the line ask for new text
                printf("Enter new text:");
                //flush the input stream
                fflush(stdin);
                //putc('\n', dstfp);
                //put '\n' in new file
                while ((c = getchar()) != '\n')
                    putc(c, dstfp);
                //take the data from user and place it in new file
                fputs("\n", dstfp);
                line++;
            }
#endif
        }
        //continue this till EOF is encountered
        c = getc(srcfp);
    }
    fclose(srcfp);
    fclose(dstfp);
    //remove(srcfile);
    //rename("replica.c", srcfile);
    srcfp = fopen("replace.result", "r");
    //reads the character from file
    c = getc(srcfp);
    //until last character of file is encountered
    while (c != EOF) {
        printf("%c", c);
        //all characters are printed
        c = getc(srcfp);
    }
    fclose(srcfp);
    printf("After Relaced file: replace.result\n");
    return 0;
}
