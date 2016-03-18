#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void die(const char *s) {
        perror(s);
        exit(1);
}

int main(int argc, char **argv) {

        /* search each element of $PATH, strcat with argv[1] to get the path to the script, then execl that.
         * need to know how to access environment variables from the c program
         */

        /* the script to run */
        char *scriptname = argv[1];
        pid_t pid;
        int status;

        /* fork */
        pid = fork();
        /* error has occured */
        if (pid < 0) {
                die("fork failed");
        }
        /* child process runs the script */
        else if (pid == 0) {
                execl(scriptname, scriptname, (char *)0);
                die("execl failed");
        }
        /* parent process waits for the child to return */
        else {
                if (waitpid(pid, &status, 0) != pid)
                        die("waitpid failed");
        }
        return 0;
}
