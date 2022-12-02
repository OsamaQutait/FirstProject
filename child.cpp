#include <iostream>

using namespace std;

#include <unistd.h>
#include <signal.h>


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
    string type = argv[1];

    kill(getpid(), SIGSTOP);
    int speed = generate_Speed(80, 100);
    usleep(speed * 20000);
    //REd sigusr1

    if (type == "red") {
        kill(getppid(), SIGUSR1);
    }
    if (type == "green") {
        kill(getppid(), SIGUSR2);
        //REd sigusr2
    }
    return 0;
}