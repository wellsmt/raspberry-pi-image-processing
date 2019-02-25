// A Huffman tree node
template<class T>
class MinHeapNode {
public:
  // One of the input characters
  T data;

  // Frequency of the character
  size_t freq;

  // Left and right child
  MinHeapNode<T> *left, *right;

  MinHeapNode<T>(const T data, const size_t freq) {
    left = right = nullptr;
    this->data = data;
    this->freq = freq;
  }
};