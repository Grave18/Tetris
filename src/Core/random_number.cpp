#include "random_number.h"
#include <ctime>

int RandomNumber::get_random_number(int min, int max)
{
	// используем static, так как это значение нужно вычислить единожды
	static constexpr double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем вычисление значения из нашего диапазона
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void RandomNumber::reset_random_number()
{
	srand(static_cast<unsigned int>(time(0))); // используем системные часы в качестве стартового значения
	rand();
}
