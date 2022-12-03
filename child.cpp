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

    speed = generate_Speed(70, 99);
    speed = (useconds_t)(10000*speed);
    usleep(speed);
    if (!strcmp(type, "red")) {
        kill(getppid(), SIGUSR1);
    }

    if (!strcmp(type, "green")) {
        kill(getppid(), SIGUSR2);
    }
}

int main(int argc, char *argv[]) {
    type = argv[1];
    signal(SIGUSR1, &handle_sigusr1);
    pause();
}