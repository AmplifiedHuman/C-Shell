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
        perror("SignalError");
    }

    while (true)
    {
        printPrompt();
        input = getInputLine();
        if (input == NULL)
        {
            puts("");
            exit(EXIT_SUCCESS);
        }
        inputTokens = getTokens(input);
        runCommand(inputTokens);
        /* Free resources before processing next command */
        free(input);
        free(inputTokens);
    }
    puts("");
    return 0;
}
