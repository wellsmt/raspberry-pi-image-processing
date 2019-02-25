#include <algorithm>
#include <cstddef>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <utility>

#include "huffman.h"
// C++ program for Huffman Coding


// Prints huffman codes from
// the root of Huffman Tree.
std::string huffman::code(const char d) {
  if(codes.find(d) != codes.end())
    return codes[d];
  return "";
}

void huffman::printCodes(struct MinHeapNode* root, std::string str){
 
	if (!root) 
		return; 

	if (root->data != '$') 
    codes[root->data] = str;

	printCodes(root->left, str + "0"); 
	printCodes(root->right, str + "1"); 
}

template <class T, class S, class C>
S &Container(std::priority_queue<T, S, C> &q) {
  struct HackedQueue : private std::priority_queue<T, S, C> {
    static S &Container(std::priority_queue<T, S, C> &q) {
      return q.*&HackedQueue::c;
    }
  };
  return HackedQueue::Container(q);
}

void huffman::print(){
  std::vector<MinHeapNode *> &tasks = Container(m_minHeap);

  for (std::vector<MinHeapNode *>::iterator i = tasks.begin(); i != tasks.end();
       i++)
    std::cout << *i << std::endl;
}

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
huffman::huffman(const std::list<std::pair<char, int>> &data) {

  struct MinHeapNode *left, *right, *top;

	// Create a min heap & inserts all characters of data[] 

	for (std::list<std::pair<char, int>>::const_iterator i = data.begin(); i != data.end(); ++i) 
  {
    std::cout << i->first << " " << i->second << std::endl;
		m_minHeap.push(new MinHeapNode(i->first, i->second)); 
  }
  // Iterate while size of heap doesn't become 1
  while (m_minHeap.size() != 1  ) {
    // Extract the two minimum
    // freq items from min heap
    left = m_minHeap.top();
    m_minHeap.pop();

    right = m_minHeap.top();
    m_minHeap.pop();

    // Create a new internal node with
    // frequency equal to the sum of the
    // two nodes frequencies. Make the
    // two extracted node as left and right children
    // of this new node. Add this node
    // to the min heap '$' is a special value
    // for internal nodes, not used
    top = new MinHeapNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    m_minHeap.push(top);
  }
 	printCodes(m_minHeap.top(), ""); 

}
