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
    bool is_recursive;
    char *input_path;
    char *output_path;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input; /* which was passed in by argp_parse below */
    switch (key) {
    case 'r': case 'R':
        arguments->is_recursive = true;
        break;
    case 'h':
    case ARGP_KEY_NO_ARGS:
        argp_state_help(state, stderr, ARGP_HELP_STD_HELP); 
        /* SEE /usr/include/argp.h __argp_usage() */
        break;
    case ARGP_KEY_ARG:
        if (state->arg_num >= args_num) { /* Too many arguments. */
            arguments->output_path = arg;
        }
        arguments->input_path = arg;
        break;
    case ARGP_KEY_END:
        if (state->arg_num < args_num) /* Not enough arguments. */
            argp_usage(state);  /* Not detail help, not the output as --help */
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

int main (int argc, char **argv) {
    struct arguments arguments;

    /* default */
    arguments.is_recursive = false;
    arguments.input_path = "-";
    arguments.output_path = "-";

    /* parse arguments */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    printf ("INPUT_PATH = %s \nOUTPUT_PATH = %s\n-R = %s\n",
            arguments.input_path,
            arguments.output_path,
            arguments.is_recursive ? "yes" : "no");

    return 0;
}
