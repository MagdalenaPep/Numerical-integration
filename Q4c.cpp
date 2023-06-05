//Define all necessary libraries
#include <iostream>
#include <iomanip>
#include <valarray>
#include <stdexcept>
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
int main(){
    // Define the integration limits and the exact integral value
    long double a = 0.0;
    long double b = 10.0;
    int N = 127;
    long double I_exact = 2.74324739415100920;
    //define  pi variable
    long double pi = 3.141592653589793238;

    //Initialize the valarrays with size 128
    valarray<long double> x_i(N + 1);
    valarray<long double> f_i(N + 1);
    valarray<long double> w_i(N + 1);

    // Fill the valarrays x_i, f_i, and w_i with grid points, function values, and weights, respectively using the for loop below.
    // For loop iterates from 0 to 127, i.e. 128 points
    for (int i = 0; i <= N; i++) {
        // Calculate theta_i based on the index i and the total number of points N
        long double theta = ((i * pi) / N);
        // Calculate the grid point xi using Clenshaw-Curtis formula provided xi =[(a+b)−(b−a)cosθi]/2
        x_i[i] = ((a + b) - (b - a) * cos(theta)) / 2.0;
        // Calculate the function value f_i at the grid point x_i
        f_i[i] = f(x_i[i]);

        // Calculate the weights w_i for the Clenshaw-Curtis quadrature rule
        if (i == 0 || i == N) {
            w_i[i] = ((b - a) /2.0) *((1.0)/(N*N));

        } else {
            long double sum = 0.0;
            for (int k = 1; k <= ((N - 1) / 2.0); k++) {
                sum += (2.0 * cos(2.0 * k * theta)) / ((4.0 * k * k )- 1.0);
            }
            w_i[i] = (((b - a) / 2.0) * (2.0 / N) * (1.0 - sum));
        }
    }

    //Calculate the integral by taking the inner product of w_i and f_i
    long double I_ClenshawCurtis = inner_product(w_i, f_i);

    // Calculate the difference between the calculated integral and the exact value
    long double difference_ClenshawCurtis = I_ClenshawCurtis - I_exact;

    // Output the results with a precision of 20 digits
    cout << setprecision(20);
    cout << "Clenshaw-Curtis rule:I_ClenshawCurtis =  " << I_ClenshawCurtis << endl;
    cout << "Difference:I_ClenshawCurtis - I_exact = " << difference_ClenshawCurtis << endl<< endl;
}