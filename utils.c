#include "shell.h"

/* Reads a line, returns NULL is EOF encountered */
char *getInputLine(void)
{
    char *inputLine = NULL;
    size_t bufSize = 0;
    int flag = getline(&inputLine, &bufSize, stdin);
    if (feof(stdin))
    {
        return NULL;
    }
    if (!flag)
    {
        perror("getLineError");
        exit(EXIT_FAILURE);
    }
    return inputLine;
}

/* Splits the given line into tokens, returns NULL if inputLine is new line character. */
char **getTokens(char *inputLine)
{
    char **args = malloc(sizeof(char *));
    if (args == NULL)
    {
        perror("MallocError");
        exit(EXIT_FAILURE);
    }
    /* if inputline is new line character, return NULL */
    if (strcmp(inputLine, "\n") == 0)
    {
        return NULL;
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
            perror("ReallocError");
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

/* Run a command using execvp or cd */
void runCommand(char **args)
{
    /* Check if command is cd, if so change directory and return (Do not create child process) */
    if (strcmp(args[0], "cd") == 0)
    {
        changeDirectory(args);
        return;
    }
    /* If command is not cd, create child proc */
    pid_t pid = fork();

    /* If child process */
    if (pid == 0)
    {
        /* Check if there's input redirection */
        if (checkRedirect(args))
        {
            /* If there's input redirection process redirection first */
            if (processRedirect(args) == 1)
            {
                /* If failed, print fail message and quit child proc */
                fprintf(stderr, "Shell: invalid redirection\n");
                exit(EXIT_FAILURE);
            }
        }
        /* Try to execute command */
        if (execvp(args[0], args) == -1)
        {
            /* If failed print error and terminate child process */
            perror("ExecutionError");
            exit(EXIT_FAILURE);
        }
    }
    /* If forking failed */
    else if (pid < 0)
    {
        perror("ForkingError");
    }
    /* If parent process */
    else
    {
        wait(&pid);
    }
}

/* Check for '>' */
bool checkRedirect(char **args)
{
    int i = 0;
    while (args[i] != NULL)
    {
        if (strcmp(args[i], ">") == 0)
        {
            return true;
        }
        i++;
    }
    return false;
}

/* Modify args and also redirects output, returns 0 if redirection is successful, 1 otherwise */
int processRedirect(char **args)
{
    int i = -1;
    while (strcmp(args[++i], ">") != 0)
    {
    }
    if (i == 0 || args[i + 1] == NULL)
    {
        return 1;
    }
    else
    {
        char *fileName = args[i + 1];
        int f = open(fileName, O_CREAT | O_WRONLY | O_TRUNC, 0666);
        /* Replace file descriptor of stdout with f */
        dup2(f, 1);
        /* NULL terminate args at position of > */
        args[i] = NULL;
    }
    return 0;
}

/* Changes the current working directory */
void changeDirectory(char **args)
{
    /* If first argument is NULL, we cd to HOME directory */
    if (args[1] == NULL)
    {
        char *homedir = getenv("HOME");
        /* Check if chdir is unsuccessful */
        if (chdir(homedir) != 0)
        {
            perror("chdirError");
        }
    }
    /* Else cd to first argument */
    else
    {
        /* Check if chdir is unsuccessful */
        if (chdir(args[1]) != 0)
        {
            perror("chdirError");
        }
    }
}