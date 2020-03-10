#include "shell.h"

void printPrompt(void)
{
    char timeBuffer[20];
    time_t now = time(NULL);
    strftime(timeBuffer, 20, "[%d/%m %H:%M]", localtime(&now));
    fprintf(stdout, "%s # ", timeBuffer);
    /* Need to flush stdout as no new line character included */
    fflush(stdout);
}