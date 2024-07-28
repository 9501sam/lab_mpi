#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

//TODO: turn it to MPI program!
int main(int argc, char *argv[])
{
    // random seed
    srand(time(NULL));

    long long circle_cnt = 0, square_cnt = 0;
    long long total_tests = strtoll(argv[1], NULL, 10);

    for (int i = 0; i < total_tests; ++i)
    {
        // random num within 0 ~ 1
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        
        double d = x*x + y*y;
        if(d <= 1) circle_cnt++;
        square_cnt++;
    }
    
    double pi = 4.0 * circle_cnt / square_cnt;
    cout << "Pi = " << pi << endl;

    return 0;
}