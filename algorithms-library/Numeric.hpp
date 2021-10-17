#pragma once
#include <vector>

std::vector<int> FindFactors(int number) {
	std::vector<int> factors;

	while (number % 2 == 0)
	{
		factors.push_back(2);
		number /= 2;
	}

	// »щем нечетные множители
	int i = 3;
	int maxFactor = static_cast<int>(sqrt(number));
	while (i <= maxFactor)
	{
		while (number % i == 0)
		{
			factors.push_back(i);
			number /= i;
			maxFactor = static_cast<int>(sqrt(number));
		}
		// ѕровер€ем следующий возможный нечетный множитель
		i += 2;
	}
	// ≈сли от числа что-то осталось, то остаток тоже множитель
	if (number > 1)
	{
		factors.push_back(number);
	}
	return factors;
}
