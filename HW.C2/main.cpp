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

	// minDistTable�� -1�� �ʱ�ȭ�Ǿ��־�� �Ѵ�.
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

	// �׷��� �籸��
	auto n = graph.nVertices;
	auto layeredGraph = new Graph[n];
	deleteList.push_back(layeredGraph);

	for (auto i = 0; i < n; ++i)
	{
		layeredGraph[i] = graph;
		// ��� �׷����� inEdge�� �����ش�.
		for (auto& vertex : layeredGraph[i].vertexList)
		{
			for (auto& inEdge : *vertex.inEdges)
				inEdge = nullptr;
		}
	}

	// �����׼� ������ edge ó��
	for (auto i = 0; i < n - 1; ++i)
	{
		for (auto eachVertex : layeredGraph[i].vertexList)
		{
			for (auto outEdge : *eachVertex.outEdges)
			{
				// �����׼� ������ edge�� dest�� �� ���� ���̾��� ������ �ٲ۴�
				outEdge->dest = &layeredGraph[i + 1].vertexList[outEdge->dest->index];
				// ������ ������ edge�� dest�� inEdge�� ���� �߰��Ѵ�.
				outEdge->dest->inEdges->push_back(outEdge);
			}
			// �����׼� �����׷� ���� edge�� ���� ������ش�.
			auto newEdge = new Edge();
			deleteList.push_back(newEdge);
			newEdge->weight = 0;
			newEdge->source = &eachVertex;
			newEdge->dest = &layeredGraph[i + 1].vertexList[eachVertex.index];
			eachVertex.outEdges->push_back(newEdge);
			layeredGraph[i + 1].vertexList[eachVertex.index].outEdges->push_back(newEdge);
		}
	}
	// ������ layer�� outEdge�� ���� �����ش�
	for (auto& vertex : layeredGraph[n - 1].vertexList)
		for (auto& outEdge : *vertex.outEdges)
			outEdge = nullptr;

	// ���� ���� �˰����� ������ �ȴ�.
	auto& newStart = layeredGraph[0].vertexList[startVertex.index];
	auto& newDest = layeredGraph[n - 1].vertexList[endVertex.index];

	// �˰��� ������ ���� �ε����� �� ��������.
	auto startIndex = layeredGraph[0].vertexList.back().index + 1;
	for (auto i = 1; i < n; ++i)
	{
		for (auto& vertex : layeredGraph[i].vertexList)
		{
			vertex.index = startIndex;
			++startIndex;
		}
	}
	// ������
	auto minDistTable = new int[startIndex];
	auto result =  MinDistRecursive(newStart, newDest, minDistTable);

	// �޸� ����
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
	// n�� �Ѱ� ������ �ϸ� �����Ѵ�.
	if (depth > nVertices)
		return;
	for (auto edge : *vertex.outEdges)
	{
		if (edge == nullptr)
			continue;
		// �̹� ������ִ� ��
		auto& currentMin = minDistTable[edge->dest->index];
		// �̹��� ���� ����� ��
		// startWeight�� ���� ������� �� �������� �ּڰ�
		auto currentValue = startWeight + edge->weight;
		if (currentValue < currentMin)
			currentMin = currentValue;
	}
	for (auto edge : *vertex.outEdges)
	{
		BottomUp_SubFunc(*edge->dest, startWeight + edge->weight, depth + 1,nVertices,minDistTable);
	}
}