//Define all necessary libraries
#include <iostream>
#include <valarray>
#include <stdexcept>
#include <iomanip>
#include <cmath>
using namespace std;

// Compute the inner product of two valarray<long double> of the same size, code copied from question 2A
long double inner_product(const valarray<long double> u, const valarray<long double> v) {
    if (u.size() != v.size()) {
        throw invalid_argument("Vectors must have the same size.");
    }
    return (u * v).sum();
}

// Function to compute the integrand f(x) = sin(1 / (x + 0.5)) at each grid point
long double f(const long double x) {
    return sin(1.0 / (x + 0.5));
}
// Function to compute the derivative of f(x) = sin(1 / (x + 0.5)), which is f'(x) = cos(1 / (x + 0.5)) * (-1 / (x + 0.5)^2)
long double derivative(const long double x) {
    return cos(1.0 / (x + 0.5)) * (-1.0 / pow(x + 0.5, 2));
}

int main() {
    // Define the integration limits and the exact integral value
    long double a = 0.0;
    long double b = 10.0;
    int N = 127;
    long double I_exact = 2.74324739415100920;

    // Calculate the grid step size and initialize the valarrays with size 128
    valarray<long double> xi(N + 1);
    valarray<long double> fi(N + 1);
    valarray<long double> wi(N + 1);

    long double g = (b - a) / (long double) N;
    // Fill the valarrays xi, fi, and wi with grid points, function values, and weights, respectively
    //For loop iterates from 0 to 127 so 128 points, first it calculates all the grid points using step g
    for (int i = 0; i <= N; i++) {
        xi[i] = a + (i * g) / 1.0; //divide by 0.1 to make sure value is a double
        fi[i] = f(xi[i]);

        if (i == 0 || i == N) {
            wi[i] = g / 2.0;
        } else {
            wi[i] = g;
        }
    }

    // Compute the integral using the composite trapezium rule
    long double I_trapezium = inner_product(wi, fi);
    // Compute the integral using the composite Hermite rule as given in the question:I_trapizium+((grid step size) ^2*(derivative(a)-derivative(b)))/12)
    long double I_Hermite = I_trapezium + ((g * g * (derivative(a) - derivative(b))) / 12.0);
    // Calculate the difference between the computed integral using Hermite rule and the exact value
    long double difference_Hermite = I_Hermite - I_exact;

    // Output the results  and differences with correct labels to 20 digits of accuracy
    cout << setprecision(20) << "Hermite rule:    I_Hermite =             " << I_Hermite << endl;
    cout << setprecision(20)<< "Difference:      I_Hermite - I_exact =   " << difference_Hermite << endl << endl;
}