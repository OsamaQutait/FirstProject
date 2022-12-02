#include <iostream>

using namespace std;

#include <unistd.h>
#include <signal.h>
#include <string.h>


int generate_Speed(int lower, int upper) {
    int s, numb;
    FILE *f;
    f = fopen("/dev/urandom", "rb");
    fread(&s, sizeof(int), 1, f);
    fclose(f);
    srand(s);
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
//
//void signal_catcher1(int sig) {
//
//
//}

int main(int argc, char *argv[]) {
    cout << "Hello, World!, child" << endl;

    const char *type = argv[1];
    cout << type << endl;


    kill(getpid(), SIGSTOP);
    int speed = generate_Speed(80, 100);
    cout << speed << endl;

    usleep(speed * 20000);
    //REd sigusr1

    if ( strcmp(type, "red") == 0) {
        cout << "iam in the red if";

             kill(getppid(), SIGUSR1);
    }
    if (strcmp(type, "green") == 0) {
        cout << "iam in the green if";

        kill(getppid(), SIGUSR2);
        //REd sigusr2
    }
    pause();
    return 0;
}