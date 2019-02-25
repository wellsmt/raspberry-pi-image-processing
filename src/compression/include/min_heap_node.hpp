namespace huffman {
// A Huffman tree node
template<class T>
class Node {
public:
  // One of the input characters
  T data;

  // Frequency of the character
  size_t freq;

  // Left and right child
  Node<T> *left, *right;

  Node<T>(const T data, const size_t freq) {
    left = right = nullptr;
    this->data = data;
    this->freq = freq;
  }
};
}