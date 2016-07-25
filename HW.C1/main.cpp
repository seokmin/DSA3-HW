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
		// ���⼭ ���� �κ��� MaxValueRecursive(i,values)�� �ƴ� ������
		// values[i]�� MaxValueRecursive(i,values)���� �� ���� ��쿡�� ���ʿ� �� �κ��� �߶��� ���� ���� �� ���� ���� �����̴�.
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

//  recursive�ϰ� �Ȱ���. �̹� �������� �ִ����� Ȯ���� �� ��.
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