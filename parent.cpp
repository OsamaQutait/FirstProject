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


int main(int argc, char *argv[]) {
    vector<pid_t> pid_array;
    pid_t pid;
    int result;
    for (int i = 0; i < 10; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("the fork fail");
            exit(-1);
        }
        if (pid == 0){
            kill(getpid(), SIGSTOP);
            break;
        } else {
            cout << pid << "  " << getppid() << endl;
            pid_array.push_back(pid);
        }
    }

    for (int i = 0; i < 5; ++i) {
        kill(pid_array[i], SIGCONT);
        if (pid == 0) {
            char* args[] = {"child", NULL};
            result = execv("./child", args);
            if (result == -1) {
                perror("execv fail");
                exit(-2);
            }
        }
    }

    cout << "Size : " << pid_array.size() << endl;
    for (int id : pid_array){
        kill(id, SIGKILL);
    }


    return 0;
}
