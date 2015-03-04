/**
 * Transform Text to Textile
 **/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <argp.h>

/* Global variables used by argp.h to show */
const char *argp_program_version = "tot 1.0";
const char *argp_program_bug_address = "<345106552@qq.com>";

/* Private variables used by this itself */
static char doc[] = "TexttoTextile, a tool to transform text to textile";
static int args_num = 1;
static char args_doc[] = "<SOURCE file|folder> [DEST folder]";
static struct argp_option options[] = {
    /* {name, key, arg, flags, doc, group}
       name, long key, --name, can not be help/usage
       key, short key, -k
       arg, the required arg after the key, -k XXX
       doc, description doc,
       If not set, it is C initialization and auto set to default value.in static
       they are set to Zero, but not in local variable initialization.
       SEE http://gnu.april.org/software/libc/manual/html_node/Argp- Option-Vectors.html
     */

    /* the name can not use 'help', 'usage' because --help, --usage already be
       used by default */
    {"help me",   'h',  0,    0, "Want a help"}, 
    {"recursive", 'r',  0,    0, "Directories recursively"},
    {"recursive", 'R',  0, OPTION_ALIAS},        /* means just like upper */
    {"verbose",   'v',  0,    0,  "Produce verbose output" },
    {"silent",    's',  0, OPTION_ALIAS},
    {"quiet",     'q',  0,    0,  "Don't produce any output" },
    {"output",    'o',  "FILE", 0, "Output to FILE instead of standard output"},
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

/*
 * KEY  – an integer specifying which option this is or a special key specifying something else.
 *   ARGP_KEY_ARG 0x0000000, meaning a non-option argument, and 
 *   ARGP_KEY_END 0x1000001, meaning that all arguments have been parsed
 *   ARGP_KEY_INIT 0x1000003, meaning it's the command name
 *   ...
 *   KEY are ARGP_KEY_XXX or the keys specifying in options[] yourself. it won't be others.
 * SEE /usr/include/argp.h
 *
 * Attention: 
 * if the KEY are not ARGP_KEY_XXX or not in the options[] upper, 
 *  it would show help directly by argp.h and would not go into parse_opt! 
 *   So ./tot -x would directly show help and would not step into swtich(key).
 *
 * ARG  – For an option KEY, the string value of its
 *        argument, or NULL if it has none
 */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input; /* which was passed in by argp_parse below */
    printf("-Parsing... | key:'%c'(0x%X) arg:'%s' \n", key, key, arg);
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
        /* Attention: 
         * once show a help, the program would exit directly from here ! */
        break;
    case ARGP_KEY_ARG:
        /* use this to force to stop the parser and return, 
           it would then go into -> ARGP_KEY_END -> ARGP_KEY_SUCCESS */
        // state->next = state->argc;
        
        /*  
         *  ./tot -r abc END
         *  when parsing abc, state->arg_num is 0, state->next is 2 
         *  arg_num: -r abc END ,so abc is index 0, and args[arg_num] = arg can hold the abc argument.
         *  next: ./tot -r abc END ,so END is the next, and index is 3, 
         *       and state->argv+state->next is the next parsing argument.
         *  Attention: 
         *  If reached the tail of the arguments, next is unchanged and equal with argc.
         *      so remaining_args_num = state->argc - state->arg_num;
         *         next_arguments = state->argv + state->next;
         *
         */

        printf("-IN ARGP_KEY_ARG | argc:%d argnum:%d next:%d\n",
               state->argc, state->arg_num, state->next);

        /* Attention: 
         * you should make sure the following state->arg_num is the right index! 
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
     */
    case ARGP_KEY_ARGS:
        printf("-IN ARGP_KEY_ARGS | ARGP_ERR_UNKNOWN was return in ARGP_KEY_ARG | argc:%d argnum:%d next:%d => you can see arg_num is 1, means the parser was broken when parsing arg_num 1, now it was immediately resumed from this index and you can handle it and the remaining arguments again,"
        " But Attention:\n"
        "    Now next is the remaining arguments's start index, not the next parsing index!\n"
        "    You won't have chance to go into ARGP_KEY_ARG again now, you have to handle remaining arguments here if you need! => You can see bellow output would NOT go into ARGP_KEY_ARG again!\n",
               state->argc, state->arg_num, state->next);
        int remain_argv_num = state->argc - state->arg_num;
        char **remain_argv = state->argv + state->next;
        int i = 0;
        printf("-REMAINS | remain_argvs_num:%d | remain_argvs:", remain_argv_num);
        for (i = 0; i < remain_argv_num; i++) {
            printf("%s ", (char *)remain_argv[i]);
        }
        printf("| => you can see remain_argvs contains a null at the end\n");
        break;
    case ARGP_KEY_END:
        printf("-End | argc:%d argnum:%d next:%d => you can see next is unchanged and equal with argc\n",
               state->argc, state->arg_num, state->next);
        //if (state->arg_num < args_num) /* Not enough arguments. */
        //    argp_usage(state);  /* Not detail help, not the output as --help */
        break;
    default:
        printf("-Unknown ARG | argc:%d argnum:%d next:%d => you can see the first step alway go into here!\n", 
               state->argc, state->arg_num, state->next);
        //return ARGP_ERR_UNKNOWN; /* Attention: always return ARGP_ERR_UNKNOWN here */
    }
    return 0;
}

static struct argp myargp = {options, parse_opt, args_doc, doc};

int main (int argc, char **argv) {
    struct arguments myarguments;

    printf("== You can use: %s 1 2 3 4 to test ==\n", argv[0]);

    /* default */
    myarguments.is_recursive = false;
    myarguments.input_path = "-";
    myarguments.output_path = "-";

    /* parse arguments */
    argp_parse(&myargp, argc, argv, 0, 0, &myarguments);

    printf ("INPUT_PATH = %s \nOUTPUT_PATH = %s\n-R = %s\n",
            myarguments.input_path,
            myarguments.output_path,
            myarguments.is_recursive ? "yes" : "no");

    return 0;
}
