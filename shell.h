/* Name: Tee Chee Guan
 * Student Number: 18202044
 * Email: chee.tee@ucdconnect.ie
 */
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

char *getInputLine(void);
char **getTokens(char *inputLine);
void runCommand(char **args);
void printPrompt(void);
void changeDirectory(char **args);
bool checkRedirect(char **args);
int processRedirect(char **args);