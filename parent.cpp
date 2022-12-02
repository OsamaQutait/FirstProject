#include <iostream>
#include <iostream>

using namespace std;

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>


vector<pid_t> pid_array;


int i = 1;

void handle_from_red(int sig) {
    kill(pid_array[i], SIGCONT);
    i++;
    if (i == 6) {
        cout << "the red team win";
        //system("pkill child");
        //goto label1
    }
}

int j = 6;

void handle_from_green(int sig) {
    kill(pid_array[j], SIGCONT);
    j++;
    if (j == 11) {
        cout << "the green team win";

    }

}

int main(int argc, char *argv[]) {

    pid_t pid;
    int result;
    char *type = "";

    for (int i = 0; i < 10; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("the fork fail");
            exit(-1);
        }
        if (pid == 0) {

            if (i < 5) {
                type = "red";
            } else {
                type = "green";
            }

            char *args[] = {"child", type, NULL};
            result = execv("./child", args);
            if (result == -1) {
                perror("execv fail");
                exit(-2);
            }

        } else {
            cout << pid << "  " << getppid() << endl;
            pid_array.push_back(pid);
        }
    }

    kill(pid_array[0], SIGCONT);//Red first one
    kill(pid_array[5], SIGCONT);//Blue first one
    signal(SIGUSR1, &handle_from_red);
    signal(SIGUSR2, &handle_from_green);

    while (1);

    cout << "Size : " << pid_array.size() << endl;
    for (int id: pid_array) {
        kill(id, SIGKILL);
    }

    label:

    return 0;
}