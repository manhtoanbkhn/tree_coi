#include <iostream>
#include "tree.h"


using BT_int = BinaryTree<int>;


int main(int argc, char** argv) {

  BT_int tree(0);

  auto root = tree.Root();

  tree.AddChildNode(root.get(), 1, BT_int::NodeType::LEFT);
  tree.AddChildNode(root.get(), 2, BT_int::NodeType::RIGHT);
  tree.AddChildNode(root->left.get(), 3, BT_int::NodeType::LEFT);
  tree.AddChildNode(root->left.get(), 4, BT_int::NodeType::RIGHT);
  tree.AddChildNode(root->right.get(), 5, BT_int::NodeType::LEFT);
  tree.AddChildNode(root->right.get(), 6, BT_int::NodeType::RIGHT);


  std::vector<int> traversal;
  tree.Traversal(root.get(), BT_int::TraversalType::IN_ORDER, traversal);
  std::cout << "in order: ";
  for (auto& x : traversal) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  traversal.clear();
  tree.Traversal(root.get(), BT_int::TraversalType::PRE_ORDER, traversal);
  std::cout << "pre order: ";
  for (auto& x : traversal) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  traversal.clear();
  tree.Traversal(root.get(), BT_int::TraversalType::POST_ORDER, traversal);
  std::cout << "post order: ";
  for (auto& x : traversal) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  traversal.clear();
  tree.Traversal(root.get(), BT_int::TraversalType::LEVEL_ORDER, traversal);
  std::cout << "level order: ";
  for (auto& x : traversal) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}