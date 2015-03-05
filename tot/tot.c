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
static int args_num = 2;
static char args_doc[] = "<SOURCE file|folder> <DEST folder>";
static struct argp_option options[] = {
    /* {name, key, arg, flags, doc, group} */
    {"help me",   'h',  0,    0, "Want a help"}, 
    {"force", 'f',  0,    0, "Replace the existing file without prompt"},
    {0, 'r',  0,    0, "Directories recursively"},
    {"recursive", 'R',  0, OPTION_ALIAS},
    {"verbose",   'v',  0,    0,  "Produce verbose output"},
    {"silent",    's',  0, OPTION_ALIAS},
    {"quiet",     'q',  0,    0,  "Don't produce any output"},
    {0} /* end with */
};

/* a custom structure to hold the arguments */
struct arguments {
    bool is_recursive;
    bool is_force;
    char *input_path;
    char *output_path;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
    case 'f': 
        arguments->is_force = true;
        break;
    case 'r':
    case 'R':
        arguments->is_recursive = true;
        break;
    case 'h':
    case ARGP_KEY_NO_ARGS:
        argp_state_help(state, stderr, ARGP_HELP_STD_HELP); 
        /* SEE /usr/include/argp.h __argp_usage() */
        break;
    case ARGP_KEY_ARG:
        switch (state->arg_num) {
        case 0: 
            arguments->input_path = arg;
            break;
        case 1: 
            arguments->output_path = arg;
            break;
        default:
            argp_usage(state);
            break;
        }
        break;
    case ARGP_KEY_END:
        if (state->arg_num < args_num) {
            argp_usage(state);
        }
        break;
    default:
        return ARGP_ERR_UNKNOWN;
        /* Attention: always return ARGP_ERR_UNKNOWN here */
    }
    return 0;
}

static struct argp myargp = {options, parse_opt, args_doc, doc};

int main (int argc, char **argv) {
    struct arguments myarguments;

    /* default */
    myarguments.is_force = false;
    myarguments.is_recursive = false;
    myarguments.input_path = "-";
    myarguments.output_path = "-";

    /* parse arguments */
    argp_parse(&myargp, argc, argv, 0, 0, &myarguments);

    printf ("INPUT_PATH = %s \nOUTPUT_PATH = %s\n-f = %s\n-R = %s\n",
            myarguments.input_path,
            myarguments.output_path,
            myarguments.is_force ? "yes" : "no",
            myarguments.is_recursive ? "yes" : "no");

    return 0;
}
