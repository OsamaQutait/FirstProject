#include "header.h"
pid_t parent_id;
vector<pid_t> pid_array;
int i = 1;
int j = 6;

void handle_sigusr1(int sig) {
    kill(pid_array[i], SIGUSR1);
    i++;
    if(i == 6) {
        cout << "the red win"<< endl;
        fflush(stdout);
//        kill(parent_id, SIGSTOP);
        exit(1);
    }
}

void handle_sigusr2(int sig) {
    kill(pid_array[j], SIGUSR1);
    j++;
    if(j == 11) {
        cout << "the green win" << endl;
        fflush(stdout);
//        kill(parent_id, SIGSTOP);
        exit(1);
    }
}

int main(int argc, char *argv[]) {

    pid_t pid;
    int result;
    char *type;

    for (int i = 0; i < 10; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("the fork fail");
            exit(-1);
        }
        if (pid == 0){
            if(i < 5){
                type = "red";
            }
            else{
                type = "green";
            }
            char* args[] = {"child", type, NULL};
            result = execv("./child", args);
            if (result == -1) {
                perror("execv fail");
                exit(-2);
            }

        } else {
            cout << pid << "  " << getppid() << endl;
            pid_array.push_back(pid);
            parent_id = getppid();
        }
    }
//    cout <<  << endl;
    sleep(1);
    kill(pid_array[0], SIGUSR1);//Red first one
    kill(pid_array[5], SIGUSR1);//Blue first one
    signal(SIGUSR1, &handle_sigusr1);
    signal(SIGUSR2, &handle_sigusr2);

    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);

//    cout << "Size : " << pid_array.size() << endl;
    for (int id : pid_array){
        kill(id, SIGKILL);
    }
    return 0;
}