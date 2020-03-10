#include "shell.h"

/* Reads a line */
char *getInputLine(void)
{
    char *inputLine = NULL;
    size_t bufSize = 0;
    int flag = getline(&inputLine, &bufSize, stdin);
    if (!flag)
    {
        fprintf(stderr, "Error: cannot read line");
        exit(EXIT_FAILURE);
    }
    return inputLine;
}

/* Splits the given line into tokens */
char **getTokens(char *inputLine)
{
    char **args = malloc(sizeof(char *));
    if (args == NULL)
    {
        fprintf(stderr, "Error: cannot allocate memory");
        exit(EXIT_FAILURE);
    }
    int count = 1;
    char *temp = strtok(inputLine, " \t\n");
    while (temp != NULL)
    {
        args[count - 1] = temp;
        count++;
        char **reallocated = realloc(args, count * sizeof(char *));
        if (reallocated == NULL)
        {
            fprintf(stderr, "Error: cannot split line.");
            exit(EXIT_FAILURE);
        }
        else
        {
            args = reallocated;
        }
        temp = strtok(NULL, " \t\n");
    }
    args[count - 1] = NULL;
    return args;
}

/* Run a command using execvp */
void runCommand(char **args)
{
    pid_t pid = fork();

    /* If child process */
    if (pid == 0)
    {
        /* Try to execute command */
        if (execvp(args[0], args) == -1)
        {
            /* If failed print error and terminate child process */
            fprintf(stderr, "Error: %s: Unknown program.\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    /* If forking failed */
    else if (pid < 0)
    {
        fprintf(stderr, "Error: forking failed");
    }
    /* If parent process */
    else
    {
        wait(&pid);
    }
}