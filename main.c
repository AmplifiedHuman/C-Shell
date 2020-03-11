/* Name: Tee Chee Guan
 * Student Number: 18202044
 * Email: chee.tee@ucdconnect.ie
 */
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
        /* If inputTokens is NULL, it means that there is only the newline character, loop again */
        if (inputTokens == NULL)
        {
            continue;
        }
        runCommand(inputTokens);
        /* Free resources before processing next command */
        free(input);
        free(inputTokens);
    }
    puts("");
    return 0;
}
