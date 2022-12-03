#include "header.h"

const char *type;
int speed;


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

void handle_sigusr1(int sig) {
    if (!strcmp(type, "red")) {
//        cout << type << " " << speed << " " << getpid() <<endl;
        kill(getppid(), SIGUSR1);
    }

    if (!strcmp(type, "green")) {
//        cout << type << " " << speed << " " << getpid() <<endl;
        kill(getppid(), SIGUSR2);
    }
}

int main(int argc, char *argv[]) {
//    cout << "Hello, World!, child" << endl;
    type = argv[1];
//    cout << type << endl;
    speed = generate_Speed(70, 99);
    speed = (useconds_t)(10000*speed);
    usleep(speed);
    signal(SIGUSR1, &handle_sigusr1);
    pause();
}