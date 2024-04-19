#include <iostream>
#include "tree.h"


using BT_int = BinaryTree<int>;

void Test_Traversal() {
  BT_int tree(0);

  auto root = tree.Root();

  tree.AddChildNode(root, 1, BT_int::NodeType::LEFT);
  tree.AddChildNode(root, 2, BT_int::NodeType::RIGHT);
  tree.AddChildNode(root->left, 3, BT_int::NodeType::LEFT);
  tree.AddChildNode(root->left, 4, BT_int::NodeType::RIGHT);
  tree.AddChildNode(root->right, 5, BT_int::NodeType::LEFT);
  tree.AddChildNode(root->right, 6, BT_int::NodeType::RIGHT);


  tree.Print(BT_int::TraversalType::IN_ORDER);
  tree.Print(BT_int::TraversalType::PRE_ORDER);
  tree.Print(BT_int::TraversalType::POST_ORDER);
  tree.Print(BT_int::TraversalType::LEVEL_ORDER);
}

void Test_Insert() {

  BT_int tree;
  BT_int::TraversalType type = BT_int::TraversalType::LEVEL_ORDER;
  tree.Print(type);

  tree.Insert(0);
  tree.Print(type);

  auto root = tree.Root();
  tree.AddChildNode(root, 1, BT_int::NodeType::LEFT);
  tree.AddChildNode(root, 2, BT_int::NodeType::RIGHT);
  tree.AddChildNode(root->left, 3, BT_int::NodeType::LEFT);
  // tree.AddChildNode(root->left, 4, BT_int::NodeType::RIGHT);
  tree.AddChildNode(root->right, 5, BT_int::NodeType::LEFT);
  tree.AddChildNode(root->right, 6, BT_int::NodeType::RIGHT);

  std::cout << "before insert" << std::endl;
  tree.Print(type);
  std::cout << "insert 4 into right of node 1" << std::endl;
  tree.Insert(4);
  tree.Print(type);
  std::cout << "insert some nodes" << std::endl;
  for (int i = 0; i < 10; ++i) {
    tree.Insert(i);
  }
  std::cout << "expect: 0 1 2 3 4 5 6 0 1 2 3 4 5 6 7 8 9" << std::endl;
  tree.Print(type);
}


int main(int argc, char** argv) {

  std::cout << "Test Traversal\n";
  Test_Traversal();

  std::cout << "\nTest Insert\n";
  Test_Insert();

}