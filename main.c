#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *readInputLine();
char **getArguments(char *line);
void executeCommand(char **args);

int main(void)
{
    bool end = false;
    char *command;
    char **tokens;
    do
    {
        printf("# ");
        command = readInputLine();
        tokens = getArguments(command);
        executeCommand(tokens);
        free(command);
    } while (!end);

    return 0;
}

/* Reads a line from stdin */
char *readInputLine()
{
    char *line = NULL;
    size_t bufferSize = 0;
    int flag = getline(&line, &bufferSize, stdin);
    /* Print error message and quit if line is not read properly */
    if (flag == EOF)
    {
        exit(EXIT_SUCCESS);
    }
    return line;
}

/* Splits the command into arguments */
char **getArguments(char *line)
{
    /* Pointer to char pointer for storing arguments, initial size is 1 */
    char **args = malloc(sizeof(char *));
    /* Error handling */
    if (args == NULL)
    {
        fprintf(stderr, "Error: cannot split line.");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    /* Try to parse first argument */
    char *temp = strtok(line, "\t\n ");
    while (temp != NULL)
    {
        args[count++] = temp;
        /* Reallocate more space for next argument */
        args = realloc(args, (count + 1) * sizeof(char *));
        /* Error handling */
        if (args == NULL)
        {
            fprintf(stderr, "Error: cannot split line.");
            exit(EXIT_FAILURE);
        }
        /* Move to next token */
        temp = strtok(NULL, " ");
    }
    /* NULL terminate the array so that we know where's the end */
    args[count] = NULL;
    return args;
}

/* Executes a give command, return 1 or 0 according to status */
void executeCommand(char **args)
{
    /* Status flag */
    int flag = 0;
    /* Create a new child */
    pid_t pid = fork();
    /* Fork error */
    if (pid < 0)
    {
        fprintf(stderr, "Error: forking error.");
    }
    /* Child process */
    else if (pid == 0)
    {
        /* Replace process with system call */
        execvp(args[0], args);
        /* If not successful print error message and exit */
        fprintf(stderr, "%s: command not found\n", args[0]);
    }
    /* Parent process */
    else
    {
        /* Wait for child */
        wait(&pid);
    }
}