
#include "truong.h"

#define DEBUG_KEY true

void usage(const char *argv)
{
    fprintf(stderr, "%s <source> <destination>\n", argv);
}

bool echo(bool on)
{
    struct termios t;

    if (tcgetattr(STDIN_FILENO, &t) == -1)
        return false;

    t.c_lflag = on ? (t.c_lflag |= ECHO) : (t.c_lflag &= ~ECHO);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
        return false;

    return true;
}

char *readkey(const char *prompt)
{
    char buf[256];
    char *p;
    size_t size;
    ssize_t n;

    printf("%s ", prompt);
    fflush(stdout);

    memset(buf, 0, sizeof(buf));

    echo(false);
    n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
    echo(true);

    if (n <= 0)
        return NULL;

    size = (size_t)n;

    if (buf[size - 1] == '\n')
        size--;

    if (size == 0)
        return NULL;

    p = malloc(size + 1);

    if (p == NULL)
        return NULL;

    memcpy(p, buf, size);
    p[size] = '\0';

    return p;
}

int main(int argc, char *argv[])
{
    char *key;

    if (argc < 3)
    {
        usage(argv[0]);
        return 1;
    }

    key = readkey("Key:");

    if (key == NULL)
    {
        fprintf(stderr, "Failed to read key\n");
        return 1;
    }

    if (DEBUG_KEY)
        printf("\n[DEBUG] Key: %s\n", key);

    free(key);

    return 0;
}