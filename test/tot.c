/**
 * Transform Text to Textile
 **/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <argp.h>

const char *argp_program_version = "tot 1.0";
const char *argp_program_bug_address = "<345106552@qq.com>";

static char doc[] = "TexttoTextile, a tool to transform text to textile";
static int args_num = 1;
static char args_doc[] = "<SOURCE file|folder> [DEST folder]";
static struct argp_option options[] = {
    /* {name, key, arg, flags, doc, group}
     * name, long key, --name
     * key, short key, -k
     * arg, the required arg after the key, -k XXX
     * doc, description doc,
     * SEE http://gnu.april.org/software/libc/manual/html_node/Argp-Option-Vectors.html
     */

    /* the name can not use 'help', 'usage' because --help, --usage already be used by default */
    {"help me",    'h',   0,    0, "Want a help"}, 
    {"recursive",  'r',   0,    0, "Directories recursively"},
    {"recursive",  'R',   0, OPTION_ALIAS},             /* means just like upper */
    {"verbose",    'v',   0,    0,  "Produce verbose output" },
    {"silent",     's',   0, OPTION_ALIAS},
    {"quiet",      'q',   0,    0,  "Don't produce any output" },
    {"output",     'o',   "FILE", 0, "Output to FILE instead of standard output" },
    { 0 }, /* end with */
    
    /* uppers would be sorted by order, bellows would be ignored, because argp_parser read from head
     * until a {0} appeared and then sort the options got */
    {"output",     'a',   "FILE", 0, "Output to FILE instead of standard output" },
};

/* a custom structure to hold the arguments */
struct arguments {
    char *args[2];      /* to store the two ARG */
    bool is_recursive;
    char *input_path;
    char *output_path;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input; /* which was passed in by argp_parse below */
    printf("-Parsing...\n");
    switch (key) {
    case 'r':
    case 'R':
        printf("R is true!\n");
        arguments->is_recursive = true;
        break;
    case 'h':
    case ARGP_KEY_NO_ARGS:
        argp_state_help(state, stderr, ARGP_HELP_STD_HELP); 
        /* SEE /usr/include/argp.h __argp_usage() */
        break;
    case ARGP_KEY_ARG:
        /*  
         *  ./tot -r abc END
         *  when parsing abc, state->arg_num is 0, state->next is 2 
         *  arg_num: -r abc END ,so abc is index 0, and args[arg_num] = arg can hold the abc argument.
         *  next: ./tot -r abc END ,so END is the next, and index is 3, 
         *       and state->argv+state->next is the next parsing argument.
         *  Attention: 
         *  If reached the tail of the arguments, next is unchanged and equal with argc.
         *      so remaining_args_num = argc - state->next;
         *         next_arguments = state->argv + state->next;
         */

        printf("-IN ARGP_KEY_ARG | argc:%d argnum:%d next:%d\n",
               state->argc, state->arg_num, state->next);

        /* Attention: you should make sure the following state->arg_num is the right index! 
         * Or its cross-border access would change the other values of the arguments structure! */
        if (state->arg_num < 2)
            arguments->args[state->arg_num] = arg;

        if (state->arg_num >= args_num) { /* Too many arguments. */
            arguments->output_path = arg;
        }
        arguments->input_path = arg;
        if (state->arg_num == 1) {
            printf("    argnum is 1, return ARGP_ERR_UNKNOWN now\n");
            return ARGP_ERR_UNKNOWN;
        }
        break;
    /* If a parser function returns ARGP_ERR_UNKNOWN for ARGP_KEY_ARG, it is immediately called again with the key ARGP_KEY_ARGS, which has a similar meaning, but is slightly more convenient for consuming all remaining arguments. 
     * ARGP_KEY_ARGS take place only:
     *      return ARGP_ERR_UNKNOWN in ARGP_KEY_ARG, not in other place.
     *      
     * */
    case ARGP_KEY_ARGS:
        printf("-IN ARGP_KEY_ARGS | ARGP_ERR_UNKNOWN was return in ARGP_KEY_ARG | argc:%d argnum:%d next:%d => you can see arg_num is 1, means the parser was broken when parsing arg_num 1, now it was immediately resumed from this index and you can handle it again,"
        " But Attention: now next is the remaining arguments's start index, not the next parsing index!\n"
        "    You won't have chance to go into ARGP_KEY_ARG again now, you have to handle remaining arguments here if you need! => You can see bellow would NOT go into ARGP_KEY_ARG again!\n",
               state->argc, state->arg_num, state->next);
        break;
    case ARGP_KEY_END:
        printf("-End | argc:%d argnum:%d next:%d => you can see next is unchanged and equal with argc\n",
               state->argc, state->arg_num, state->next);
        if (state->arg_num < args_num) /* Not enough arguments. */
            argp_usage(state);  /* Not detail help, not the output as --help */
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp myargp = {options, parse_opt, args_doc, doc};

int main (int argc, char **argv) {
    struct arguments arguments;

    /* default */
    arguments.is_recursive = false;
    arguments.input_path = "-";
    arguments.output_path = "-";

    /* parse arguments */
    argp_parse(&myargp, argc, argv, 0, 0, &arguments);

    printf ("INPUT_PATH = %s \nOUTPUT_PATH = %s\n-R = %s\n%d\n%d\n",
            arguments.input_path,
            arguments.output_path,
            arguments.is_recursive ? "yes" : "no", arguments.is_recursive, false);

    return 0;
}
