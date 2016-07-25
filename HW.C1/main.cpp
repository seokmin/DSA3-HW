#include <iostream>
#include <stdlib.h>

int MaxValueRecursive(int rodSize, int* values);

int MaxValueRecursiveMemo(int rodSize, int* values);
int MaxValueRecursiveMemo_SubF(int rodSize, int* values, int* memo);

int MaxValueBottomUp(int rodSize, int* values);

int MaxValueBottomUpForPrint(int rodSize, int* values, int* cutPosition);
void PrintRodLength(int rodSize, int* cutPosition);

int main(void)
{


	return 0;
}

int MaxValueRecursive(int rodSize, int* values)
{
	if (rodSize == 0)
		return 0;
	auto maxValue = INT_MIN;
	for (auto i = 1; i <= rodSize; ++i)
	{
		// 여기서 앞의 부분이 MaxValueRecursive(i,values)가 아닌 이유는
		// values[i]가 MaxValueRecursive(i,values)보다 더 작은 경우에는 애초에 그 부분을 잘랐을 때가 답이 될 수가 없기 때문이다.
		auto currentValue = values[i] + MaxValueRecursive(rodSize - i, values);
		if (currentValue > maxValue)
			maxValue = currentValue;
	}
	return maxValue;
}

int MaxValueRecursiveMemo(int rodSize, int* values)
{
	if (rodSize == 0)
		return 0;

	auto memo = new int[rodSize + 1];
	for (auto i=0; i<=rodSize;++i)
		i = -1;

	auto maxValue = MaxValueRecursiveMemo_SubF(rodSize, values, memo);

	delete[] memo;

	return maxValue;
}

//  recursive하고 똑같다. 이미 구한적이 있는지만 확인해 줄 뿐.
int MaxValueRecursiveMemo_SubF(int rodSize, int* values, int* memo)
{
	if (memo[rodSize] != -1)
		return memo[rodSize];

	if (rodSize == 0)
		return 0;

	auto maxValue = INT_MIN;
	for (auto i = 1; i <= rodSize; ++i)
	{
		auto currentValue = values[i] + MaxValueRecursiveMemo_SubF(rodSize - i, values, memo);
		if (currentValue < maxValue)
			maxValue = currentValue;
	}
	memo[rodSize] = maxValue;

	return maxValue;
}

int MaxValueBottomUp(int rodSize, int* values)
{
	auto maxValues = new int[rodSize + 1];
	maxValues[0] = 0;
	for (auto i = 1; i <= rodSize; ++i)
	{
		auto maxValue = INT_MIN;
		for (auto j = 1; j <= i; ++j)
		{
			auto currentvalue = values[j] + maxValues[i - j];
			if (maxValue < currentvalue)
				maxValue = currentvalue;
		}
		maxValues[i] = maxValue;
	}
	auto result = maxValues[rodSize];
	delete[] maxValues;
	return result;
}

int MaxValueBottomUpForPrint(int rodSize, int* values, int* cutPosition)
{
	auto maxValues = new int[rodSize + 1];
	maxValues[0] = 0;
	cutPosition[0] = 0;
	for (auto i = 1; i <= rodSize; ++i)
	{
		auto maxValue = INT_MIN;
		for (auto j = 1; j <= i; ++j)
		{
			auto currentvalue = values[j] + maxValues[i - j];
			if (maxValue < currentvalue)
			{
				maxValue = currentvalue;
				cutPosition[i] = j;
			}
		}
		maxValues[i] = maxValue;
	}
	auto result = maxValues[rodSize];
	delete[] maxValues;
	return result;
}

void PrintRodLength(int rodSize, int* cutPosition)
{
	auto remainLength = rodSize;
	while(remainLength >0)
	{
		std::cout << cutPosition[remainLength] << " ";
		remainLength -= cutPosition[remainLength];
	}
	std::cout << std::endl;

	return;
}