#include <iostream>
using namespace std;
#include <unistd.h>
#include <signal.h>



int generate_Speed(int lower, int upper)
{
    int s, numb;
    FILE *f;
    f = fopen("/dev/urandom", "rb");
    fread(&s, sizeof(int), 1, f);
    fclose(f);
    srand(s);
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void signal_catcher1(int sig){


}


int main(int argc, char *argv[]) {
    cout << "Hello, World!, child" << endl;
    int speed = generate_Speed(80,100);
    usleep(speed*10000);
    signal(SIGUSR1, signal_catcher1);
    return 0;
}
