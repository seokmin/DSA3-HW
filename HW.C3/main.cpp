#include <iostream>
#include <limits.h>
#include <list>


struct MatrixInfo
{
	int row;
	int column;
};

int MinCostRecursive(MatrixInfo* matrixes, int startBlock, int endBlock)
{
	if (startBlock == endBlock)
		return 0;
	auto minValue = INT_MAX;
	for (auto cutBlock = startBlock; cutBlock < endBlock; ++cutBlock)
	{
		auto currentValue = MinCostRecursive(matrixes, startBlock, cutBlock) + MinCostRecursive(matrixes, cutBlock + 1, endBlock)
			+ matrixes[startBlock].row * matrixes[cutBlock].column * matrixes[endBlock].column;
		if (minValue > currentValue)
			minValue = currentValue;
	}
	return minValue;
}

int MinCostMemoization(MatrixInfo* matrixes, int startBlock, int endBlock, int** minMatrix)
{
	if (minMatrix[startBlock][endBlock] != -1)
		return minMatrix[startBlock][endBlock];

	if (startBlock == endBlock)
	{
		minMatrix[startBlock][endBlock] = 0;
		return 0;
	}
	auto minValue = INT_MAX;

	for (auto cutBlock = startBlock; cutBlock < endBlock; ++cutBlock)
	{
		auto currentValue = MinCostRecursive(matrixes, startBlock, cutBlock) + MinCostRecursive(matrixes, cutBlock + 1, endBlock)
			+ matrixes[startBlock].row * matrixes[cutBlock].column * matrixes[endBlock].column;
		if (minValue > currentValue)
			minValue = currentValue;
	}

	minMatrix[startBlock][endBlock] = minValue;
	return minValue;
}

int MinCostBottomUp(MatrixInfo* matrixes, int n)
{
	std::list<void*> deleteList;

	auto minMatrix = new int*[n];

	for (auto i = 0; i < n; ++i)
	{
		minMatrix[i] = new int[n];
		deleteList.push_back(minMatrix[i]);
		// 자신끼리 곱하는건 0으로 초기화
		minMatrix[i][i] = 0;
	}

	// 작은 덩어리를 채워야 큰 덩어리를 채울 수 있다
	for (int gap = 1; gap < n; ++gap)
	{
		for (int startblock = 0; startblock < n - gap; ++startblock)
		{
			auto endBlock = startblock + gap;
			auto currentMin = INT_MAX;
			for (int cutBlock = startblock; cutBlock < endBlock; ++cutBlock)
			{
				auto currentVal = minMatrix[startblock][cutBlock] + minMatrix[cutBlock + 1][endBlock]
					+ matrixes[startblock].row	* matrixes[cutBlock].column * matrixes[endBlock].column;
				if (currentMin > currentVal)
					currentMin = currentVal;
			}
			minMatrix[startblock][endBlock] = currentMin;
		}
	}

	auto result = minMatrix[0][n - 1];

	//메모리 정리
	delete[] minMatrix;
	for (auto& i : deleteList)
		delete i;

	return result;
}


int main(void)
{
	MatrixInfo matrixes[] = { {3,2},{2,4},{4,2},{2,1} };
	std::cout << MinCostBottomUp(matrixes,4);
	std::cin >> matrixes[0].column;
	return 0;
};