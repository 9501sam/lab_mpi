#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <mpi.h>  // Include the MPI header

using namespace std;

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);  // Initialize MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the number of processes

    // Seed the random number generator with a unique seed for each process
    srand(time(NULL) + rank);

    long long circle_cnt = 0, square_cnt = 0;
    long long total_tests = strtoll(argv[1], NULL, 10);

    // Distribute the number of tests among processes
    long long local_tests = total_tests / size;
    long long local_circle_cnt = 0;

    // Each process performs its local number of tests
    for (long long i = 0; i < local_tests; ++i) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        double d = x * x + y * y;
        if (d <= 1) local_circle_cnt++;
    }

    // Use MPI_Reduce to sum up all local_circle_cnt to get the global circle count
    MPI_Reduce(&local_circle_cnt, &circle_cnt, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate pi in the root process (rank 0)
    if (rank == 0) {
        square_cnt = total_tests;  // Total number of square counts
        double pi = 4.0 * circle_cnt / square_cnt;
        cout << "Pi = " << pi << endl;
    }

    MPI_Finalize();  // Finalize MPI
    return 0;
}

