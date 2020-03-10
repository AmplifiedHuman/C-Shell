#include "shell.h"

/* Reads a line */
char *getInputLine(void)
{
    char *inputLine = NULL;
    size_t bufSize = 0;
    int flag = getline(&inputLine, &bufSize, stdin);
    if (!flag)
    {
        perror("Error");
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
        perror("Error");
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
            perror("Error");
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
        /* Check if command is cd */
        if (strcmp(args[0], "cd") == 0)
        {
            changeDirectory(args);
        }
        /* Try to execute command */
        else if (execvp(args[0], args) == -1)
        {
            /* If failed print error and terminate child process */
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
    /* If forking failed */
    else if (pid < 0)
    {
        perror("Error");
    }
    /* If parent process */
    else
    {
        wait(&pid);
    }
}

void changeDirectory(char **args)
{
    /* If first argument is NULL, we cd to HOME directory */
    if (args[1] == NULL)
    {
        char *homedir = getenv("HOME");
        /* Check if chdir is successful */
        if (chdir(homedir) != 0)
        {
            perror("Error");
        }
    }
    /* Else cd to first argument */
    else
    {
        /* Check if chdir is successful */
        if (chdir(args[1]) != 0)
        {
            perror("Error");
        }
    }
}