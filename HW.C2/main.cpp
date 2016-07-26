#include <map>
#include <vector>
#include <list>
const int MAX_VERTEX = 1024;

struct Edge
{
	Vertex* source;
	Vertex* dest;
	int weight;
};

struct Vertex
{
	int index;
	std::vector<Edge*>* inEdges;
	std::vector<Edge*>* outEdges;
};

int MinDistRecursive(Vertex& startVertex, Vertex& endVertex, int* minDistTable)
{
	if (startVertex.index == endVertex.index)
		return 0;

	// minDistTable은 -1로 초기화되어있어야 한다.
	if (minDistTable[endVertex.index] != -1)
		return minDistTable[endVertex.index];

	auto minValue = INT_MAX;
	for (auto& currentEdge : *endVertex.inEdges)
	{
		auto currentVal = currentEdge->weight + MinDistRecursive(startVertex, *currentEdge->source, minDistTable);
		if (minValue < currentVal)
			minValue = currentVal;
	}
	minDistTable[endVertex.index] = minValue;

	return minValue;
}

struct Graph
{
	std::vector<Vertex&> vertexList;
	int nVertices;
};

int MinDistCycleRecursive(Vertex& startVertex, Vertex& endVertex, Graph& graph)
{
	std::list<void*> deleteList;

	// 그래프 재구성
	auto n = graph.nVertices;
	auto layeredGraph = new Graph[n];
	deleteList.push_back(layeredGraph);

	for (auto i = 0; i < n; ++i)
	{
		layeredGraph[i] = graph;
		// 모든 그래프의 inEdge를 없애준다.
		for (auto& vertex : layeredGraph[i].vertexList)
		{
			for (auto& inEdge : *vertex.inEdges)
				inEdge = nullptr;
		}
	}

	// 나한테서 나가는 edge 처리
	for (auto i = 0; i < n - 1; ++i)
	{
		for (auto eachVertex : layeredGraph[i].vertexList)
		{
			for (auto outEdge : *eachVertex.outEdges)
			{
				// 나한테서 나가는 edge의 dest를 내 다음 레이어의 놈으로 바꾼다
				outEdge->dest = &layeredGraph[i + 1].vertexList[outEdge->dest->index];
				// 나한테 나가는 edge의 dest의 inEdge에 나를 추가한다.
				outEdge->dest->inEdges->push_back(outEdge);
			}
			// 나한테서 나한테로 가는 edge를 새로 만들어준다.
			auto newEdge = new Edge();
			deleteList.push_back(newEdge);
			newEdge->weight = 0;
			newEdge->source = &eachVertex;
			newEdge->dest = &layeredGraph[i + 1].vertexList[eachVertex.index];
			eachVertex.outEdges->push_back(newEdge);
			layeredGraph[i + 1].vertexList[eachVertex.index].outEdges->push_back(newEdge);
		}
	}
	// 마지막 layer의 outEdge를 전부 없애준다
	for (auto& vertex : layeredGraph[n - 1].vertexList)
		for (auto& outEdge : *vertex.outEdges)
			outEdge = nullptr;

	// 이제 기존 알고리즘을 돌리면 된다.
	auto& newStart = layeredGraph[0].vertexList[startVertex.index];
	auto& newDest = layeredGraph[n - 1].vertexList[endVertex.index];

	// 알고리즘 돌리기 전에 인덱스를 쭉 맞춰주자.
	auto startIndex = layeredGraph[0].vertexList.back().index + 1;
	for (auto i = 1; i < n; ++i)
	{
		for (auto& vertex : layeredGraph[i].vertexList)
		{
			vertex.index = startIndex;
			++startIndex;
		}
	}
	// 돌린다
	auto minDistTable = new int[startIndex];
	auto result =  MinDistRecursive(newStart, newDest, minDistTable);

	// 메모리 정리
	delete[] minDistTable;
	for (auto& pointer : deleteList)
		delete pointer;

	return result;
}

int MinDistCycleBottomUp(Vertex& startVertex, Vertex& endVertex, int* minDistTable, int nVertices)
{
	for (auto i = 0; i < MAX_VERTEX; ++i)
		minDistTable[i] = INT_MAX;

	BottomUp_SubFunc(startVertex, 0, 1,nVertices,minDistTable);

	return minDistTable[endVertex.index];
}

int BottomUp_SubFunc(Vertex& vertex, int startWeight, int depth,int nVertices, int* minDistTable)
{
	// n번 넘게 돌려고 하면 제지한다.
	if (depth > nVertices)
		return;
	for (auto edge : *vertex.outEdges)
	{
		if (edge == nullptr)
			continue;
		// 이미 저장돼있던 놈
		auto& currentMin = minDistTable[edge->dest->index];
		// 이번에 새로 계산한 놈
		// startWeight는 지금 여기까지 올 때까지의 최솟값
		auto currentValue = startWeight + edge->weight;
		if (currentValue < currentMin)
			currentMin = currentValue;
	}
	for (auto edge : *vertex.outEdges)
	{
		BottomUp_SubFunc(*edge->dest, startWeight + edge->weight, depth + 1,nVertices,minDistTable);
	}
}