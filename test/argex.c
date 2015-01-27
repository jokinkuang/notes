#include <stdio.h>
#include <string.h>
#include <argp.h>

#define NAME_LEN 100
#define ADDR_LEN 500

const char *argp_program_version =
"bigex 1.0";

const char *argp_program_bug_address =
"<bug-gnu-utilsgnu.org>";


/* This structure is used by main to communicate with parse_opt. */
struct arguments
{
  char *args[1];            /* No arguments to this function */
  int verbose;              /* The -v flag */
  char *infile;             /* Argument for -i */
  char *outfile;            /* Argument for -o */
};


struct personal_data
{
  char name[NAME_LEN];
  char address[ADDR_LEN];
  struct personal_data *next;
};


/*
  OPTIONS.  Field 1 in ARGP.
  Order of fields: {NAME, KEY, ARG, FLAGS, DOC}.
*/
static struct argp_option options[] =
  {
    {"verbose", 'v', 0, 0, "Produce verbose output"},

    {"input",   'i', "INFILE",  0,
     "Read addresses from INFILE"},

    {"output",  'o', "OUTFILE", 0,
     "Output to OUTFILE instead of to standard output"},

    {0}
  };


/*
  PARSER. Field 2 in ARGP.
  Order of parameters: KEY, ARG, STATE.
*/
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'v':
      arguments->verbose = 1;
      break;
    case 'i':
      arguments->infile = arg;
      break;
    case 'o':
      arguments->outfile = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
	{
	  argp_usage(state);
	}
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
	{
	  argp_usage (state);
	}
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}


/*
  ARGS_DOC. Field 3 in ARGP.
  A description of the non-option command-line arguments
  that we accept.
*/
static char args_doc[] = "ARG";


/*
  DOC.  Field 4 in ARGP.
  Program documentation.
*/
static char doc[] =
"bigex -- Add ARG new names to an address book file.\vThe largest code example in the GNU C Tutorial.";


/*
  The ARGP structure itself.
*/
static struct argp argp = {options, parse_opt, args_doc, doc};


struct personal_data *
new_empty_node()
{
  struct personal_data *new_node;

  new_node =  (struct personal_data*)
    malloc (sizeof (struct personal_data));

  strcpy (new_node->name, "");
  strcpy (new_node->address, "");
  new_node->next = NULL;

  return new_node;
}


struct personal_data *
create_node()
{
  int bytes_read;
  int nbytes;

  struct personal_data *current_node;
  char *name;
  char *address;

  current_node = new_empty_node();

  puts ("Name?");
  nbytes = NAME_LEN;
  name = (char *) malloc (nbytes + 1);
  bytes_read = getline (&name, &nbytes, stdin);
  if (bytes_read == -1)
    {
      puts ("ERROR!");
    }
  else
    {
      strncpy (current_node->name, name, NAME_LEN);
      free (name);
    }

  puts ("Address?");
  nbytes = ADDR_LEN;
  address = (char *) malloc (nbytes + 1);
  bytes_read = getline (&address, &nbytes, stdin);
  if (bytes_read == -1)
    {
      puts ("ERROR!");
    }
  else
    {
      strncpy (current_node->address, address, ADDR_LEN);
      free (address);
    }

  printf("\n");
  return current_node;
}



struct personal_data *
find_end_node (struct personal_data *current_node)
{
  if (current_node->next == NULL)
    {
      return current_node;
    }
  else
    {
      return find_end_node (current_node->next);
    }
}


int
list_length (struct personal_data *root)
{
  struct personal_data *current_node;
  int count = 0;

  current_node = root;

  while (current_node->next != NULL)
    {
      current_node = current_node->next;
      count++;
    }
  return count;
}


struct personal_data *
find_node (struct personal_data *root,
	   int node_wanted)
{
  struct personal_data *current_node;
  int index = 0;

  current_node = root;

  while ((index < node_wanted) && (current_node->next != NULL))
    {
      current_node = current_node->next;
      index++;
    }
  return current_node;
}



delete_node (struct personal_data *root,
	     int location)
{
  struct personal_data *previous_node;
  struct personal_data *current_node;

  previous_node = find_node (root, location - 1);
  current_node = find_node (root, location);
  previous_node->next = current_node->next;
}



insert_node (struct personal_data *root,
	     struct personal_data *new_node,
	     int location)
{
  struct personal_data *temp_ptr;
  struct personal_data *previous_node;

  previous_node = find_node (root, location - 1);
  temp_ptr = previous_node->next;

  previous_node->next = new_node;
  new_node->next = temp_ptr;
}


swap_nodes (struct personal_data *root, int a, int b)
{
  int temp;
  struct personal_data *node_a;
  struct personal_data *node_b;
  struct personal_data *temp_node;

  if (a > b)
    {
      temp = a;
      a = b;
      b = temp;
    }

  node_b = find_node (root, b);
  delete_node (root, b);

  node_a = find_node (root, a);
  delete_node (root, a);

  insert_node (root, node_b, a);
  insert_node (root, node_a, b);
}


sort_list (struct personal_data *root)
{
  int i, j, list_len, diff;

  list_len = list_length (root);
  for (i=2; i<=list_len; i++)
    {
      j = i;
      while (strcmp ( (find_node(root, j))->name,
		      (find_node(root, j-1))->name) < 0)
	{
	  swap_nodes (root, j, j-1);
	  j--;
	}
    }
}


print_node (struct personal_data *current_node,
	    FILE *save_stream)
{
  fprintf (save_stream, "%s%s",
	   current_node->name,
	   current_node->address);
}


print_list (struct personal_data *current_node,
	    FILE *save_stream)
{
  print_node (current_node, save_stream);

  if (current_node->next != NULL)
    {
      print_list (current_node->next, save_stream);
    }
}




struct personal_data *
read_node (FILE *instream)
{
  int bytes_read;
  int nbytes;

  struct personal_data *current_node;
  char *name;
  char *address;
  char *blankline;
  int read_err = 0;

  current_node = new_empty_node();

  nbytes = NAME_LEN;
  name = (char *) malloc (nbytes + 1);
  bytes_read = getline (&name, &nbytes, instream);
  if (bytes_read == -1)
    {
      read_err = 1;
    }
  else
    {
      puts (name);
      strncpy (current_node->name, name, NAME_LEN);
      free (name);
    }

  nbytes = ADDR_LEN;
  address = (char *) malloc (nbytes + 1);
  bytes_read = getline (&address, &nbytes, instream);
  if (bytes_read == -1)
    {
      read_err = 1;
    }
  else
    {
      puts (address);
      strncpy (current_node->address, address, ADDR_LEN);
      free (address);
    }

  if (read_err)
    {
      return NULL;
    }
  else
    {
      return current_node;
    }
}


struct personal_data *
read_file (char *infile)
{
  FILE *input_stream = NULL;
  struct personal_data *root;
  struct personal_data *end_node;
  struct personal_data *current_node;

  root = new_empty_node();
  end_node = root;

  input_stream = fopen (infile, "r");
  if (input_stream)
    {
      while (current_node = read_node (input_stream))
	{
	  end_node->next = current_node;
	  end_node = current_node;
	  end_node->next = NULL;
	}
    }
  return root;
}



/*
  The main function.
  Notice how now the only function call needed to process
  all command-line options and arguments nicely
  is argp_parse.
*/
int
main (int argc, char **argv)
{
  struct arguments arguments;
  struct personal_data *root;
  struct personal_data *end_node;
  struct personal_data *current_node;
  int i, newnum;
  FILE *save_stream;


  /* Set argument defaults */
  arguments.infile = NULL;
  arguments.outfile = NULL;
  arguments.verbose = 0;

  /* Where the magic happens */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  if (arguments.infile)
    {
      root = read_file (arguments.infile);
      end_node = find_end_node (root);
    }
  else
    {
      root = new_empty_node();
      end_node = root;
    }

  /* Where do we send output? */
  if (arguments.outfile)
    save_stream = fopen (arguments.outfile, "w");
  else
    save_stream = stdout;

  newnum = atoi (arguments.args[0]);

  for (i = 1; i <= newnum; i++)
    {
      current_node = create_node();
      end_node->next = current_node;
      end_node = current_node;
      end_node->next = NULL;
    }

  sort_list (root);
  print_list (root->next, save_stream);

  /* Close stream; skip error-checking for brevity of example */
  fclose (save_stream);

  /* If in verbose mode, print song stanza */
  if (arguments.verbose)
    {};

  return 0;
}
