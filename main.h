#ifndef MAIN_H
#define MAIN_H
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>/*temporary*/

/*MACROS AND EXTERNELY DEFINED VARIABLES*/
extern char **environ;/*the environment global variable*/
#define ENDOFFILE -2
extern int counter;
extern char *program_name;

/*DATA_STRUCTURES USED*/

/**
 * struct builtin_command- A struct type that defines builtin commands
 * @name: command name for the builtin
 * @function: A function pointer to command's function
 */
typedef struct builtincomm
{
	char *name;
	int(*function)(char **av, char **start);

} builtincomm_t;

/**
 * struct linked_list_s- A linked list struct
 * @path: path for a directory
 * @next: pointer to next node in the list
 */
typedef struct linked_list_s
{
	char *path;
	struct linked_list_s *next;
} linkedlist_t;

/*LINKED LIST HELPER FUNCTIONS*/
linkedlist_t *add_node_end(linkedlist_t **head, char *dirpath);
void free_linked_list(linkedlist_t *head);
/*MAIN SHELL prompt and helper functions*/
void print_prompt(int a);
int is_interactive(void);
void free_av(char **av, char **head);


/*INBUILT COMMANDS*/
int myexit(char **args, char **front);
int _cd(char **args, char **head);
/*COMMAND EXECUTION*/
int execute_cmd(int *execute_return);
int exec_command(char **av, char **head);
int (*run_builtin_cmd(char *command))(char **av, char **head);
int run_command(char **av, char **head, int *execute_return);
int check_for_logical_ops(char **av, char **head, int *execute_return);
char *extract_command_av(char *line, int *execute_return);

/*HANDLING THE ENVIRON*/
char **copyenviron(void);
void free_env(void);
char **mygetenv(const char *env_var);

/*PATH HANDLERS*/
char *find_command_in_path(char *command);
linkedlist_t *tokenize_path(char *dirpath);
char *append_cwd(char *dirpath);

/*ERRORS*/
int print_error(char **av, int err_val);
char *permission_denied_126(char **av);
char *command_not_found_127(char **av);
char *generate_error_message(char **av, const char *format, const char *extra);

/*string functions*/

char *integer_tostring(int number);
int _strcmp(char *s1, char *s2);
size_t _strlen(const char *str);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);

/*OTHER FUNCTIONS*/
int find_length(int n);/*find length of an integer number*/

char **mystrtok(char *string, char *delim);
int count_tokens(char *str, char *delim);
int delim_index(char *str, char *delim);

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
#endif
