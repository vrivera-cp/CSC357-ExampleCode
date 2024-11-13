#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    signal(SIGINT, SIG_IGN);
    char *args[] = {"./loop", NULL};
    execvp("./loop", args);
}