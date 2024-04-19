#ifndef TREE_COI_TREE_H
#define TREE_COI_TREE_H

#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <string>


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

  using NodePtr = std::shared_ptr<Node<Datatype>>;

  // @brief Create empty tree
  BinaryTree();
  // @brief Create tree with a root node
  // @param data: data of root node
  BinaryTree(const Datatype& data);
  NodePtr Root() const {
    return root_;
  }
  int Height(NodePtr node);
  int Height();
  void NodesSameLevel(NodePtr root, int level, std::vector<Datatype>& result);
  // @brief Insert into tree a new node, traversal tree by level order,
  // if left or right child is empty, insert into
  void Insert(const Datatype& data);

  void Print(TraversalType type);

  // @brief Add child (left or right) for a node, can replace old
  void AddChildNode(NodePtr node,
                    const Datatype& data,
                    NodeType node_type);
  void Traversal(NodePtr node, TraversalType type, std::vector<Datatype>& result);

 private:
  NodePtr root_;
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
  return Height(root_);
}

template <class Datatype>
int BinaryTree<Datatype>::Height(NodePtr node) {
  if (node == nullptr) return 0;
  int left_height = Height(node->left);
  int right_height = Height(node->right);
  return left_height > right_height ? left_height + 1 : right_height + 1;
}

template <class Datatype>
void BinaryTree<Datatype>::NodesSameLevel(NodePtr root, int level, std::vector<Datatype>& result) {
  if (root == nullptr) return;
  if (level == 1) result.push_back(root->data);
  else if (level > 1) {
    NodesSameLevel(root->left, level - 1, result);
    NodesSameLevel(root->right, level - 1, result);
  }
}

template <class Datatype>
void BinaryTree<Datatype>::Insert(const Datatype& data) {

  if (root_ == nullptr) {
    *this = BinaryTree<Datatype>(data);
    return;
  }

  std::queue<NodePtr> nodes;
  nodes.push(root_);

  while (!nodes.empty()) {

    auto node = nodes.front();
    nodes.pop();

    if (node->left == nullptr) {
      AddChildNode(node, data, NodeType::LEFT);
      return;
    }
    else {
      nodes.push(node->left);
    }

    if (node->right == nullptr) {
      AddChildNode(node, data, NodeType::RIGHT);
      return;
    }
    else {
      nodes.push(node->right);
    }
  }

}

template <class Datatype>
void BinaryTree<Datatype>::Print(TraversalType type) {
  std::vector<Datatype> traversal;
  Traversal(root_, type, traversal);
  if (traversal.size() == 0) {
    std::cout << "Tree is empty." << std::endl;
    return;
  }
  std::string prefix;
  switch (type)
  {
  case TraversalType::PRE_ORDER:
    prefix = "Pre order: ";
    break;
  case TraversalType::IN_ORDER:
    prefix = "In order: ";
    break;
  case TraversalType::POST_ORDER:
    prefix = "Post order: ";
    break;
  case TraversalType::LEVEL_ORDER:
    prefix = "Level order: ";
    break;
  default:
    std::cout << "unknown tree type" << std::endl;
    return;
  }
  std::cout << prefix;
  for (auto& x : traversal) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

template <class Datatype>
void BinaryTree<Datatype>::AddChildNode(NodePtr node,
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
void BinaryTree<Datatype>::Traversal(NodePtr node, TraversalType type, std::vector<Datatype>& result) {
  if (node == nullptr) return;

  if (type == TraversalType::IN_ORDER) {
    Traversal(node->left, type, result);
    result.push_back(node->data);
    Traversal(node->right, type, result);
  }
  else if (type == TraversalType::PRE_ORDER) {
    result.push_back(node->data);
    Traversal(node->left, type, result);
    Traversal(node->right, type, result);
  }
  else if (type == TraversalType::POST_ORDER) {
    Traversal(node->left, type, result);
    Traversal(node->right, type, result);
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