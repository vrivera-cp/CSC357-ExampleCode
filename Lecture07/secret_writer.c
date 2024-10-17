#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SECRET_FILE_NAME    "secret.bin"
#define SECRET_TEXT         "Hello Mochi!"
#define SECRET_ENCRYPTION   7

#define BEFORE_SPACE    16
#define AFTER_SPACE     20

int checked_write(int f, const void *buf, size_t count)
{
    if (write(f, buf, count) == -1)
    {
        perror("Failed to write to file");
        close(f);
        return -1;
    }
    return 0;
}

int main()
{
    char secret[] = SECRET_TEXT;
    
    // Open File
    int f = open(SECRET_FILE_NAME, O_CREAT | O_WRONLY, 0666);
    if (f == -1)
    {
        perror("Error opening file");
        return 1;
    }

    // Write garbage before secret
    for (char i = 0; i < BEFORE_SPACE; i++)
    {
        int garbage = random();
        if (checked_write(f, &garbage, sizeof(char)) != 0)
        {
            return 1;
        }
    }

    // Encrypt Secret
    for (int i = 0; i < strlen(secret); i++)
    {
        secret[i] += SECRET_ENCRYPTION;
    }

    // Write Encrypted Secret
    if (checked_write(f, secret, sizeof(secret)) != 0)
    {
        return 1;
    }

    // Write garbage after secret
    for (char i = 0; i < AFTER_SPACE; i++)
    {
        int garbage = random();
        if (checked_write(f, &garbage, sizeof(char)) != 0)
        {
            return 1;
        }
    }
    
    // Close File
    if (close(f) == -1)
    {
        perror("Error closing file");
        return -1;
    }

    return 0;
}