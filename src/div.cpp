//
// Created by chris on 2/1/26.
//

#include <stdexcept>
// A simple function to test
int divide(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Division by zero");
	}
	return numerator / denominator;
}