#include "shell.h"

int main(int argc, char **argv)
{
    char *input;
    char **inputTokens;
    char timeBuffer[20];

    /* Try to catch SIGINT Signal */
    if (signal(SIGINT, SIG_IGN) == SIG_ERR)
    {
        fprintf(stderr, "Error: cannot catch signal\n");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        /* If EOF key entered terminate program */
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        time_t now = time(NULL);
        strftime(timeBuffer, 20, "[%d/%m %H:%M]", localtime(&now));
        fprintf(stdout, "%s # ", timeBuffer);
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
