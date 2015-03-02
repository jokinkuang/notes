#include <stdlib.h>
#include <argp.h>

/*
 * only can show a help
 */

int
main (int argc, char **argv)
{
      argp_parse (0, argc, argv, 0, 0, 0);
        exit (0);
}
