#pragma once
#include <vector>

std::vector<int> FindFactors(int number) {
	std::vector<int> factors;

	while (number % 2 == 0)
	{
		factors.push_back(2);
		number /= 2;
	}

	// Ищем нечетные множители
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
		// Проверяем следующий возможный нечетный множитель
		i += 2;
	}
	// Если от числа что-то осталось, то остаток тоже множитель
	if (number > 1)
	{
		factors.push_back(number);
	}
	return factors;
}


std::vector<int> FindPrimes(long max_number) {
	bool* is_composite = new bool[max_number + 1];

	// Исключаем числа, кратные 2
	for (unsigned i = 0; i < max_number; i += 2)
	{
		is_composite[i] = true;
	}

	// Исключаем числа, кратные найденным простым числам
	int next_prime = 3;
	int stop_at = static_cast<int>(sqrt(max_number));
	while (next_prime <= stop_at)
	{
		// Исключаем числа, кратные данному простому числу
		for (unsigned i = next_prime * 2; i < max_number; i += next_prime)
		{
			is_composite[i] = true;
		}

		// Переходим к следующему простому числу, пропуская четные числа
		next_prime += 2;
		while (next_prime <= max_number && is_composite[next_prime]) {
			next_prime += 2;
		}
	}
	std::vector<int> primes;
	for (unsigned i = 0; i < max_number; i++)
	{
		if (!is_composite[i]) {
			primes.push_back(i);
		}
	}
	return primes;
}

float UseRectangleRule(float (*function)(float), float xmin, float xmax, int num_intervals) {
	float dx = (xmax - xmin) / num_intervals;

	float total_area = 0;
	float x = xmin;
	for (unsigned i = 1; i < num_intervals; i++)
	{
		total_area += dx * function(x);
		x += dx;
	}
	return total_area;
}


float UseTrapezoidRule(float (*function)(float), float xmin, float xmax, int num_intervals) {
	float dx = (xmax - xmin) / num_intervals;
	
	float total_area = 0;
	float x = xmin;
	for (unsigned i = 1; i < num_intervals; i++)
	{
		total_area += dx * (function(x) + function(x + dx)) / 2;
		x += dx;
	}
	return total_area;
}

float SliceArea(float (*function)(float), float x1, float x2, float max_slice_error) {
	
	// Вычисляем значение функции на конечной и центральной точках
	float y1 = function(x1);
	float y2 = function(x2);
	float xm = (x1 + x2) / 2;
	float ym = function(xm);

	// Вычисляем площадь большой трапеции и двух меньших трапеций
	float area12 = (x2 - x1) * (y1 + y2) / 2.0;
	float area1m = (xm - x1) * (y1 + ym) / 2.0;
	float aream2 = (x2 - xm) * (ym + y2) / 2.0;
	float area1m2 = area1m + aream2;

	// Оцениваем, насколько мы близко
	float error = (area1m2 - area12) / area12;

	// Оцениваем погрешность
	if (abs(error) < max_slice_error) {
		return area1m2;
	}

	// Погрешность слишком большая, делим трапецию и пробуем еще раз
	return SliceArea(function, x1, xm, max_slice_error) + SliceArea(function, xm, x2, max_slice_error);
}

float IntegrateAdaptiveMidpoint(float (*function)(float), float xmin, float xmax, int num_intervals, float max_slice_error) {
	float dx = (xmax - xmin) / num_intervals;

	float total_area = 0;
	float x = xmin;
	for (unsigned i = 1; i < num_intervals; i++)
	{
		total_area += SliceArea(function, x, x + dx, max_slice_error);
		x += dx;
	}
	return total_area;
}

float NewtonsMethod(float (*f)(float), float (*dfdx)(float), float initial_guess, float max_error) {
	float x = initial_guess;
	for (unsigned i = 0; i < 100; i++)
	{
		float y = f(x);
		if (abs(y) < max_error) {
			break;
		}

		x = (x - y) / dfdx(x);
	}
	return x;
}