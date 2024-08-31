#include "train_struct.c"
#include <unistd.h>
#include <fcntl.h>

int main() {
    Train_DB trains[] = {{
        .train_number = 123,
        .train_name = "EXPRESS A",
        .tickets_booked = 0
    }, {
        .train_number = 235,
        .train_name = "EXPRESS B",
        .tickets_booked = 0
    }, {
        .train_number = 568,
        .train_name = "EXPRESS C",
        .tickets_booked = 0
    }};

    int fd = open("db", O_CREAT | O_TRUNC | O_EXCL | O_RDWR, 0644);

    write(fd, &trains, sizeof(trains));

    return 0;
}