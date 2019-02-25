#include <functional>
#include <list>
#include <map>
#include <queue>
#include <string>

// A Huffman tree node
struct MinHeapNode {

  // One of the input characters
  char data;

  // Frequency of the character
  unsigned freq;

  // Left and right child
  MinHeapNode *left, *right;

  MinHeapNode(char data, unsigned freq) {
    left = right = nullptr;
    this->data = data;
    this->freq = freq;
  }
};

struct compare { 

	bool operator()(MinHeapNode* l, MinHeapNode* r) 

	{ 
		return (l->freq > r->freq); 
	} 
};

class huffman {

public:
  explicit huffman(const std::list<std::pair<char, int>> &data);
  ~huffman(){}

  void print();
  std::string code(const char d);
  std::map<char, std::string> codes;
private:
  std::string code(const char d, struct MinHeapNode *root, std::string str);
	std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, compare> m_minHeap;
  void printCodes(struct MinHeapNode* root, std::string str);
};
