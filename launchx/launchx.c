#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void die(const char *s) {
        perror(s);
        exit(1);
}

int main(int argc, char **argv) {

        /* search each element of $PATH, strcat with argv[1] to get the path to the script, then execl that.
         * need to know how to access environment variables from the c program
         */

        /* get the script to run */
        char *path_var = getenv("PATH");
        char *path = strtok(path_var, ":");
        char scriptpath[1000];
        strcpy(scriptpath, path);
        while ( 1 ) {
                strcat(scriptpath, "/");
                strcat(scriptpath, argv[1]);
                //printf("%s\n", scriptpath);
        
                if (!access(scriptpath, F_OK)) {
                        break;
                }

                path = strtok(NULL, ":");
                if (path == NULL) {
                        /* after checking everything in PATH, try PWD, if that fails program doesnt exist */
                        strcpy(scriptpath, getenv("PWD"));
                        strcat(scriptpath, "/");
                        strcat(scriptpath, argv[1]);
                        if (!access(scriptpath, F_OK)) {
                                break;
                        }

                        fprintf(stderr, "error: %s not found\n", argv[1]);
                        return 1;
                }
                strcpy(scriptpath, path);
        }

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
                execl(scriptpath, scriptpath, (char *)0);
                die("execl failed");
        }
        /* parent process waits for the child to return */
        else {
                if (waitpid(pid, &status, 0) != pid)
                        die("waitpid failed");
        }
        return 0;

}
