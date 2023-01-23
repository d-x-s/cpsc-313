#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd_a = open("a.txt", O_RDONLY); // = 3
    int fd_b = open("b.txt", O_RDONLY);

    pid_t child_pid = fork();

    int fd_c;
    int fd_d;

    if (child_pid > 0) { // parent process only
        fd_c = open("c.txt", O_RDONLY);
        fd_d = dup(fd_c);
    } else if (child_pid == 0) { // child process only
        fd_c = open("c.txt", O_RDONLY);
        fd_d = dup(fd_c);
    }

    return 0;
}
