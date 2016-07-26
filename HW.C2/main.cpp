#include <map>
const int MAX_VERTEX = 1024;

struct Edge
{
	Vertex* child;
	int weight;
};

struct Vertex
{
	int index;
	Edge* edges[MAX_VERTEX];
};

void CaclulateMinDistance(Vertex& startVertex, int* minDistTable)
{
	for (auto i = 0; i < MAX_VERTEX; ++i)
		minDistTable[i] = INT_MAX;

	auto recursiveCalc = [&](auto& vertex, int startWeight)
	{
		for (auto& edge : vertex.edges)
		{
			if (edge == nullptr)
				continue;
			// 이미 저장돼있던 놈
			auto& currentMin = minDistTable[edge->child->index];
			// 이번에 새로 계산한 놈
			auto currentValue = startWeight + edge->weight;
			if (currentValue < currentMin)
				currentMin = currentValue;
		}
		for (auto& edge : vertex.edges)
		{
			recursiveCalc(edge->child, startWeight + edge->weight);
		}
	};
	

}