#include "header.h"

pid_t parent_id;
vector<pid_t> pid_array;
int N = 0;
unordered_map<int, string> location_map;
int i = 1;
int j = 6;
int flag = 0;
int stop = 0;
int red_team_score = 0;
int green_team_score = 0;

void handle_sigusr1(int sig) {
    cout << RED << "Red team player move "<< location_map[i] << endl;
    fflush(stdout);
    kill(pid_array[i], SIGUSR1);
    i++;
    if(i == 6 && !stop) {
        red_team_score++;
        N++;
        cout << BLUE << "Round " << N << " finish" << " the red win"<< endl;
        fflush(stdout);
        stop = 1;
        if(red_team_score >= 5 || green_team_score >= 5 ) {
            cout << BLUE << "End of game " << endl;
            cout << BLUE << "red team score " << red_team_score << endl;
            cout << BLUE << "green team score " << green_team_score << endl;
            if (red_team_score > green_team_score){
                cout << BLUE << "the red team win" << endl;
            } else {
                cout << BLUE << "the green team win" << endl;
            }
            exit(0);
        }
        i = 1;
        j = 6;
        if (flag) {
            sleep(2);
            kill(pid_array[0], SIGUSR1);//Red first one
            kill(pid_array[5], SIGUSR1);//Blue first one
            flag = 0;
        } else {
            flag = 1;
        }
        stop = 0;
    }
}

void handle_sigusr2(int sig) {
    cout << GREEN<< "Green team player move " << location_map[j-5] << endl;
    fflush(stdout);
    kill(pid_array[j], SIGUSR1);
    j++;
    if(j == 11 && !stop) {
        green_team_score++;
        N++;
        cout << BLUE << "Round " << N << " finish" << " the green win" << endl;
        fflush(stdout);
        stop = 1;
        if(red_team_score >= 5 || green_team_score >= 5 ) {
            cout << BLUE<< "End of game " << endl;
            cout << BLUE << "red team score " << red_team_score << endl;
            cout << BLUE << "green team score " << green_team_score << endl;
            if (red_team_score > green_team_score){
                cout << BLUE << "the red team win" << endl;
            } else {
                cout << BLUE << "the green team win" << endl;
            }
            exit(0);
        }
        i = 1;
        j = 6;
        if (flag) {
            sleep(2);
            kill(pid_array[0], SIGUSR1);//Red first one
            kill(pid_array[5], SIGUSR1);//Blue first one
            flag = 0;
        } else {
            flag = 1;
        }
        stop = 0;
    }
}

int main(int argc, char *argv[]) {

    location_map[1] = "from A1 to A2";
    location_map[2] = "from A2 to A3";
    location_map[3] = "from A3 to A4";
    location_map[4] = "from A4 to A5";
    location_map[5] = "from A5 to A1";

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
            pid_array.push_back(pid);
            parent_id = getppid();
        }
    }
    sleep(1);
    kill(pid_array[0], SIGUSR1);//Red first one
    kill(pid_array[5], SIGUSR1);//Blue first one
    signal(SIGUSR1, &handle_sigusr1);
    signal(SIGUSR2, &handle_sigusr2);

    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);

    for (int id : pid_array){
        kill(id, SIGKILL);
    }
    return 0;
}
