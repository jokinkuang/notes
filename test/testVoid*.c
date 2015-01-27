#include <stdio.h>
#define PTRINT_SHORT
#ifdef PTRINT_SHORT
typedef short ptrint;
#endif
#ifdef PTRINT_INT
typedef int ptrint;
#endif
#ifdef PTRINT_LONG
typedef long ptrint;
#endif
#ifdef PTRINT_LONGLONG
typedef long long ptrint;
#endif

int main(void) {
if (sizeof(ptrint) != sizeof(void*)) {
 printf ("ERROR: ptrint doesn't match void* for this platform.\n");
 printf ("   sizeof(void*    ) = %d\n", sizeof(void*));
 printf ("   sizeof(ptrint   ) = %d\n", sizeof(ptrint));
 printf ("   =================\n");
 printf ("   sizeof(void*    ) = %d\n", sizeof(void*));
 printf ("   sizeof(short    ) = %d\n", sizeof(short));
 printf ("   sizeof(int      ) = %d\n", sizeof(int));
 printf ("   sizeof(long     ) = %d\n", sizeof(long));
 printf ("   sizeof(long long) = %d\n", sizeof(long long));
 return 1;
}
 /* rest of your code here */
 return 0;
}
