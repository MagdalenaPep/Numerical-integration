//Define all necessary libraries
#include <iostream>
#include <iomanip>
#include <random>

#include <cmath>
using namespace std;

// Function to compute the integrand f(x) = sin(1 / (x + 0.5)) at each grid point
long double f(const long double x) {
    return sin(1.0 / (x + 0.5));
}

int main() {
    // Define the integration limits and the exact integral value
    long double a = 0.0;
    long double b = 10.0;
    long double I_exact = 2.74324739415100920;

    // Declare a random number generator with a seed value 31 for a uniform distribution for a range a to b.
    mt19937_64 generator(31);
    uniform_real_distribution<double> unif(a, b);

    // Define an array to store the number of samples for each test
    int N_size[] = {1000, 10000, 100000};

    // Calculate the mean value Monte Carlo estimate using a for loop for each N
    for (int i_x = 0; i_x < 3; i_x++) {
        int N = N_size[i_x];
        long double sum = 0.0; //define a variable to store the sum

        // Generate N uniform random samples and evaluate the function at these points
        for (int i = 0; i < N; i++) {
            long double x = unif(generator);
            sum += f(x);
        }

        // Calculate the Monte Carlo estimate using the mean value method.((b-a)/N *(f(x))
        long double I_MonteCarlo = ((b - a) /  N) * sum;

        // Calculate the difference between the computed integral and the exact value
        long double difference_MonteCarlo = I_MonteCarlo - I_exact;

        // Output the results with a precision of 20 digits
        cout << setprecision(20);
        cout << "Mean Value Monte Carlo (N = " << N << "):  I_MonteCarlo = " << I_MonteCarlo << endl;
        cout << "Difference: I_MonteCarlo - I_exact = " << difference_MonteCarlo << endl;
        cout << endl;
    }
    return 0;}