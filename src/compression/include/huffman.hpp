#include <list>
#include <map>
#include <queue>
#include <string>
#include <sstream>
#include <vector>

#include "huffman_node.hpp"
namespace huffman {

typedef std::list<std::pair<char, size_t>> Char;
typedef std::list<std::pair<int, size_t>> Int;

/**
 * A class that builds a Huffman Encoding Tree and stores each character encoding for lookup.
 * @note https://en.wikipedia.org/wiki/Huffman_coding.
 */
template<class T>
class Tree {
public:
  /**
   * A constructor.
   * Builds Huffman tree from data and encodes it.
   * @param a std::list of std::pair<value, count>
   */
  explicit Tree(const std::list<std::pair<T, size_t>> &data) {
    auto compare = [](Node<T>* l, Node<T>* r){ return (l->count > r->count); };
    Node<T> *left, *right, *top;

    std::priority_queue<Node<T>*, std::vector<Node<T>*>, decltype(compare)> minHeap(compare);

    for(auto it = data.begin(); it != data.end(); ++it) 
    {
      minHeap.push(new Node(it->first, it->second)); 
    }
    
    while (minHeap.size() != 1  ) {
      left = minHeap.top();
      minHeap.pop();

      right = minHeap.top();
      minHeap.pop();

      top = new Node(T('*'), left->count + right->count);

      top->left = left;
      top->right = right;

      minHeap.push(top);
    }
    printCodes(minHeap.top(), ""); 
  }

  /**
   * A default destructor
   */
  virtual ~Tree(){}

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
   * @param huffman::Node<T>* representing the root of the Huffman Tree
   * @param std::string the encoded string
   */
  void printCodes(Node<T>* root, std::string str){
	  if (!root) 
		  return; 

	  if (root->data != T('*'))
      m_codes[root->data] = str;

	  printCodes(root->left, str + "0"); 
	  printCodes(root->right, str + "1"); 
  }
};

}
