#include <set>
#include <queue>
#include <list>

int main(void)
{
	return 0;
}
struct Node
{
	Node* left= nullptr;
	Node* right = nullptr;
	int freq = 0;
	// c는 leaf node일때만 의미를 가짐
	char c = 0;
};

auto comp = [](Node* x, Node* y) { return y->freq > x->freq; };
using MinHeap = std::priority_queue < Node*, std::vector<Node*>, decltype(comp)>;

Node* MakeHuffmanTree(std::list<Node*> nodes)
{
	MinHeap Q(comp);
	for (auto& i : nodes)
		Q.push(i);

	auto makeNewNode = [](auto a, auto b) 
	{
		// a가 무조건 b보다 작다
		auto newNode = new Node();
		newNode->left = a;
		newNode->right = b;
		newNode->freq = a->freq + b->freq;
		return newNode;
	};
	for (auto i = 0; i < nodes.size(); ++i)
	{
		auto first = Q.top();
		Q.pop();
		auto second = Q.top();
		Q.pop();
		auto newNode = makeNewNode(first, second);
		Q.push(newNode);
	}
	return Q.top();
}