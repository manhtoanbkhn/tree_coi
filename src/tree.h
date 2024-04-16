#ifndef TREE_COI_TREE_H
#define TREE_COI_TREE_H

#include <iostream>
#include <vector>
#include <memory>


template <class Datatype>
struct Node {
  Node(const Datatype& _data) {
    data = _data;
  }
  Datatype data;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;
};

template <class Datatype>
class BinaryTree {
 public:
  enum NodeType {
    PARENT,
    LEFT,
    RIGHT
  };

  enum TraversalType {
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    LEVEL_ORDER
  };

  // @brief Create empty tree
  BinaryTree();
  // @brief Create tree with a root node
  // @param data: data of root node
  BinaryTree(const Datatype& data);
  std::shared_ptr<Node<Datatype>> Root() const {
    return root_;
  }
  int Height(Node<Datatype>* node);
  int Height();
  void NodesSameLevel(Node<Datatype>* root, int level, std::vector<Datatype>& result);
  void Insert(const Datatype& data);

  // @brief Add child (left or right) for a node, can replace old
  void AddChildNode(Node<Datatype>* node,
                    const Datatype& data,
                    NodeType node_type);
  // void Print();
  void Traversal(Node<Datatype>* node, TraversalType type, std::vector<Datatype>& result);

 private:
  std::shared_ptr<Node<Datatype>> root_;
};

template <class Datatype>
BinaryTree<Datatype>::BinaryTree() {

}

template <class Datatype>
BinaryTree<Datatype>::BinaryTree(const Datatype& data) {
  root_ = std::make_shared<Node<Datatype>>(data);
}

template <class Datatype>
int BinaryTree<Datatype>::Height() {
  return Height(root_.get());
}

template <class Datatype>
int BinaryTree<Datatype>::Height(Node<Datatype>* node) {
  if (node == nullptr) return 0;
  int left_height = Height(node->left.get());
  int right_height = Height(node->right.get());
  return left_height > right_height ? left_height + 1 : right_height + 1;
}

template <class Datatype>
void BinaryTree<Datatype>::NodesSameLevel(Node<Datatype>* root, int level, std::vector<Datatype>& result) {
  if (root == nullptr) return;
  if (level == 1) result.push_back(root->data);
  else if (level > 1) {
    NodesSameLevel(root->left.get(), level - 1, result);
    NodesSameLevel(root->right.get(), level - 1, result);
  }
}

template <class Datatype>
void BinaryTree<Datatype>::Insert(const Datatype& data) {

}

template <class Datatype>
void BinaryTree<Datatype>::AddChildNode(Node<Datatype>* node,
                                        const Datatype& data,
                                        NodeType node_type) {
  if (node == nullptr) return;
  if (node_type == NodeType::LEFT) {
    node->left = std::make_shared<Node<Datatype>>(data);
  }
  else if (node_type == NodeType::RIGHT) {
    node->right = std::make_shared<Node<Datatype>>(data);
  }
}

template <class Datatype>
void BinaryTree<Datatype>::Traversal(Node<Datatype>* node, TraversalType type, std::vector<Datatype>& result) {
  if (node == nullptr) return;

  if (type == TraversalType::IN_ORDER) {
    Traversal(node->left.get(), type, result);
    result.push_back(node->data);
    Traversal(node->right.get(), type, result);
  }
  else if (type == TraversalType::PRE_ORDER) {
    result.push_back(node->data);
    Traversal(node->left.get(), type, result);
    Traversal(node->right.get(), type, result);
  }
  else if (type == TraversalType::POST_ORDER) {
    Traversal(node->left.get(), type, result);
    Traversal(node->right.get(), type, result);
    result.push_back(node->data);
  }
  else if (type == TraversalType::LEVEL_ORDER) {
    int height = Height(node);
    for (int i = 1; i <= height; ++i) {
      std::vector<Datatype> elements;
      NodesSameLevel(node, i, elements);
      result.reserve(result.size() + elements.size());
      result.insert(result.end(), elements.begin(), elements.end());
      // result.append_range(elements); // C++23 only!!!
    }
  }

}

#endif // TREE_COI_TREE_H