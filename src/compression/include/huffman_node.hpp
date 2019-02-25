namespace huffman {
template<class T>
class Node {
public:
  T data;
  size_t count;

  Node<T> *left, *right;

  Node<T>(const T data, const size_t count) {
    left = right = nullptr;
    this->data = data;
    this->count = count;
  }
};
}
