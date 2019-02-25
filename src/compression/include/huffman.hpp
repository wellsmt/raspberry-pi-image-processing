#include <functional>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>
#include <sstream>

#include "min_heap_node.hpp"
/**
 * A class that builds a Huffman Encoding Tree and stores each character encoding for lookup.
 * @note https://en.wikipedia.org/wiki/Huffman_coding.
 */
template<class T>
class huffman {
public:
  /**
   * A constructor.
   * Builds Huffman tree from data and encodes it.
   * @param a std::list of std::pair<value, count>
   */
  explicit huffman(const std::list<std::pair<T, int>> &data) {
    auto compare = [](MinHeapNode<T>* l, MinHeapNode<T>* r){ return (l->freq > r->freq); };
    MinHeapNode<T> *left, *right, *top;

    std::priority_queue<MinHeapNode<T>*, std::vector<MinHeapNode<T>*>, decltype(compare)> minHeap(compare);

    for(auto it = data.begin(); it != data.end(); ++it) 
    {
      minHeap.push(new MinHeapNode(it->first, it->second)); 
    }
    
    while (minHeap.size() != 1  ) {
      left = minHeap.top();
      minHeap.pop();

      right = minHeap.top();
      minHeap.pop();

      top = new MinHeapNode(T('*'), left->freq + right->freq);

      top->left = left;
      top->right = right;

      minHeap.push(top);
    }
    printCodes(minHeap.top(), ""); 
  }

  /**
   * A default destructor
   */
  virtual ~huffman(){}

  /**
   * Returns the encoded string based on input value from m_codes.
   * @param T value used in lookup.
   * @return std::string encoded string of "0" and "1", empty string if key not present.
   */
  const std::string code(const T d) {
    if(m_codes.find(d) != m_codes.end())
      return m_codes[d];

    std::stringstream error_string("");
    error_string << d << "is not an encoded string.";
    throw std::range_error(error_string.str());
  }
private:
  std::map<T, std::string> m_codes; /**< holdes encoded value from Huffman Tree */

  /**
   * Recursive function designed to create encoded string of a specific value.
   * @param MinHeapNode<T>* representing the root of the Huffman Tree
   * @param std::string the encoded string
   */
  void printCodes(MinHeapNode<T>* root, std::string str){
	  if (!root) 
		  return; 

	  if (root->data != T('*'))
      m_codes[root->data] = str;

	  printCodes(root->left, str + "0"); 
	  printCodes(root->right, str + "1"); 
  }
};
