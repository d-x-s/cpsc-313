#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd_a = open("hello.txt", O_RDONLY); // = 3
    int fd_b = open("hello.txt", O_RDONLY);
    int fd_c = dup(fd_b);

    pid_t child_pid = fork();

    int fd_d;

    if (child_pid == 0) { // child process only
        fd_d = open("flag.txt", O_RDONLY);
        dup2(fd_d, fd_b);
    }

    int fd_e = dup(fd_b);
    int fd_f = open("note.md", O_RDONLY);

    return 0;
}
