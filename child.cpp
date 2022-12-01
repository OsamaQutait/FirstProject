#include <iostream>
using namespace std;

int generate_random_number(int lower, int upper)
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
int main(int argc, char *argv[]) {
    cout << "Hello, World!, child" << endl;
    return 0;
}
