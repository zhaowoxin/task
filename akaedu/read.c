#include <unistd.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    char buf[32];
    int n;

    n = read(STDIN_FILENO, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, n);

    return 0;
}
