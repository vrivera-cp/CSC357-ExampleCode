#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    alarm(atoi(argv[1])); // Triggers SIGALRM after argv[1] seconds
    pause();
    return 0;
}