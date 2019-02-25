#include <functional>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>

// A Huffman tree node
template<class T>
class MinHeapNode {
public:
  // One of the input characters
  T data;

  // Frequency of the character
  unsigned freq;

  // Left and right child
  MinHeapNode<T> *left, *right;

  MinHeapNode<T>(T data, unsigned freq) {
    left = right = nullptr;
    this->data = data;
    this->freq = freq;
  }
};

template<class T>
class huffman {
public:
  explicit huffman(const std::list<std::pair<T, int>> &data) {
    auto compare = [](MinHeapNode<T>* l, MinHeapNode<T>* r){ return (l->freq > r->freq); };
    MinHeapNode<T> *left, *right, *top;

    // Create a min heap & inserts all characters of data[] 
    std::priority_queue<MinHeapNode<T>*, std::vector<MinHeapNode<T>*>, decltype(compare)> minHeap(compare);

    for(auto it = data.begin(); it != data.end(); ++it) 
    {
      minHeap.push(new MinHeapNode(it->first, it->second)); 
    }
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1  ) {
      // Extract the two minimum
      // freq items from min heap
      left = minHeap.top();
      minHeap.pop();

      right = minHeap.top();
      minHeap.pop();

      // Create a new internal node with
      // frequency equal to the sum of the
      // two nodes frequencies. Make the
      // two extracted node as left and right children
      // of this new node. Add this node
      // to the min heap '$' is a special value
      // for internal nodes, not used
      top = new MinHeapNode(T('$'), left->freq + right->freq);

      top->left = left;
      top->right = right;

      minHeap.push(top);
    }
    printCodes(minHeap.top(), ""); 
  }

  virtual ~huffman(){}

  const std::string code(const T d) {
    if(m_codes.find(d) != m_codes.end())
      return m_codes[d];
    return "";
  }
private:
  std::map<T, std::string> m_codes;

  void printCodes(MinHeapNode<T>* root, std::string str){
	  if (!root) 
		  return; 

	  if (root->data != T('$'))
      m_codes[root->data] = str;

	  printCodes(root->left, str + "0"); 
	  printCodes(root->right, str + "1"); 
  }
};
