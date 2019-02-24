#include <algorithm>
#include <cstddef>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <queue>
// C++ program for Huffman Coding 
// A Huffman tree node 
struct MinHeapNode { 

	// One of the input characters 
	char data; 

	// Frequency of the character 
	unsigned freq; 

	// Left and right child 
	MinHeapNode *left, *right; 

	MinHeapNode(char data, unsigned freq)
	{ 
		left = right = nullptr; 
		this->data = data; 
		this->freq = freq; 
	} 
};

// Prints huffman codes from 
// the root of Huffman Tree. 
std::string printCodes(struct MinHeapNode* root, std::string str) 
{
	if (!root) return ""; 
    else if (root->data != '$') return str; 
    else 
    {
	    printCodes(root->left, str + "0"); 
	    printCodes(root->right, str + "1");
    }
} 

template <class T, class S, class C>
S& Container(std::priority_queue<T, S, C>& q) {
    struct HackedQueue : private std::priority_queue<T, S, C> {
        static S& Container(std::priority_queue<T, S, C>& q) {
            return q.*&HackedQueue::c;
        }
    };
    return HackedQueue::Container(q);
}

// The main function that builds a Huffman Tree and 
// print codes by traversing the built Huffman Tree 
std::string HuffmanCodes(std::list<std::pair<char, int>> data) 
{ 
	struct MinHeapNode *left, *right, *top; 
  auto predicate = [](MinHeapNode* l, MinHeapNode* r){ return (l->freq > r->freq); };

	std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, decltype( predicate )> minHeap( predicate ); 
  std::vector<MinHeapNode*> &tasks = Container(minHeap);

  auto newNode = [](std::pair<char, int>& d){ return new MinHeapNode(d.first, d.second); };
  std::for_each(data.begin(), data.end(), newNode);

  std::cout<<std::endl<<"Reading numbers in the queue"<<std::endl;
    for(std::vector<MinHeapNode*>::iterator i=tasks.begin();i!=tasks.end();i++)
        std::cout<<*i<<std::endl;
/*
	// Iterate while size of heap doesn't become 1 
	while (minHeap.size() != 1) { 

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
		top = new MinHeapNode('$', left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		minHeap.push(top);
	} 
*/
	// Print Huffman codes using 
	// the Huffman tree built above 
	return printCodes(minHeap.top(), ""); 
}
