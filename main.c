#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char *readInputLine();
char **getArguments(const char *line);

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
        printf("%s", command);
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
    if (flag == -1)
    {
        fprintf(stderr, "Error: cannot read line.");
        exit(EXIT_FAILURE);
    }
    return line;
}

/* Splits the command into arguments */
char **getArguments(const char *line)
{
}