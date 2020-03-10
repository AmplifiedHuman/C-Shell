#include "shell.h"

void sigINTGHandler(int signno)
{
    puts("");
    printPrompt();
}

int main(int argc, char **argv)
{
    char *input;
    char **inputTokens;

    /* Try to catch SIGINT Signal */
    if (signal(SIGINT, sigINTGHandler) == SIG_ERR)
    {
        fprintf(stderr, "Error: cannot catch signal");
    }

    while (!feof(stdin))
    {
        printPrompt();
        input = getInputLine();
        inputTokens = getTokens(input);
        runCommand(inputTokens);
        /* Free resources before processing next command */
        free(input);
        free(inputTokens);
    }
    puts("");
    return 0;
}
