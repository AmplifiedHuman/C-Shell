#include "shell.h"

int main(int argc, char **argv)
{
    char *input;
    char **inputTokens;
    while (true)
    {
        printf("# ");
        /* Need to flush stdout as no new line character included */
        fflush(stdout);
        input = getInputLine();
        inputTokens = getTokens(input);
        runCommand(inputTokens);
        /* Free resources before processing next command */
        free(input);
        free(inputTokens);
    }

    return 0;
}
