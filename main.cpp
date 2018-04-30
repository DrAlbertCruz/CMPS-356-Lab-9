#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

/*
*	Function that reads data from a CSV into a 2-D array.
*	There should not be a need to change this.
*/
template <size_t rows, size_t cols>
void readCSV(double(&array)[rows][cols], std::string filename) {
	std::ifstream file(filename);

	for (size_t row = 0; row < rows; ++row)
	{
		std::string line;
		std::getline(file, line);

		if (!file.good())
			break;

		std::stringstream iss(line);

		for (size_t col = 0; col < cols; ++col)
		{
			std::string val;
			std::getline(iss, val, ',');

			std::stringstream convertor(val);
			convertor >> array[row][col];
		}
	}
}

/*
*	Function that displays data values. Only needed if you want to test.
*	There should not be a need to change this.
*/
template <size_t rows, size_t cols>
void displayValues(double(&array)[rows][cols]) {
	std::cout << "X Y" << std::endl;
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; col++) {
			std::cout << array[row][col] << ' ';
		}

		std::cout << std::endl;
	}
}

/*
*	Check fitness. Takes coefficients as input.
*	a * x^3 + b * x^2 + c * w + d
* 	Takes a, b, c and d as input. This is the sum squared error.
*/
template <size_t rows, size_t cols>
double checkFitness(double(&array)[rows][cols], int a, int b, int c, int d) {
	//For each sample
	double x, yd, y, sse = 0;
	for (int row = 0; row < rows; ++row)
	{
		// Error for each point is calculated as:
		// sum_{for all x points} ( f(x) - g(x) ) 
		// where f is the true value (from data) and g is the esimated data from the line
		x = array[row][0];
		yd = array[row][1];
		y = a * pow( x, 3 ) + b * pow( x, 2 ) + c * x + d;
		sse += pow( yd - y, 2 );
	}
	return sse;
} 


int main(int argc, char* argv[])
{
	// Load the array
	const int n = 201;
	const int m = 2;
	double data[n][m];

	readCSV<n,m>(data, "data.csv");

	// Output values to ensure they were loaded properly.
	displayValues<n,m>(data);

	//A function for checking the fitness of a cubic polynomial
	std::cout << "SSE test for original values: " << checkFitness( data, -3, 4, -5, 6) << std::endl;
	// Note that the above are the true values I used to obtain the points. There was some noise added.

	std::cout << "SSE test for wrong values: " << checkFitness( data, 0, 0, 0, 0) << std::endl;
	// Note that the above are the true values I used to obtain the points. There was some noise added.

	std::cout << "Note that the values are less for the wrong values. Correct values will not be perfect because I corrupted the data with noise." << std::endl;

	return 0;
}




