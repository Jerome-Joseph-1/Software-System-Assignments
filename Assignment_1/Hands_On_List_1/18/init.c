#include "record_struct.c"
#include <fcntl.h>
#include <unistd.h>

int main() {
    Record r[] = {
        {.data = "Hello World"},
        {.data = "Second Record"},
        {.data = "World Record"},
        {.data = "Record Three"},
    };

    int fd = open("records", O_CREAT | O_TRUNC | O_RDWR, 0644);

    write(fd, r, sizeof(r));

    return 0;
}