// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>
#include <chrono>
#include <random>
class PMTree {
 public:
  struct Node {
    char value;
    std::vector<std::unique_ptr<Node>> children;
    explicit Node(char val) : value(val) {}
  };
  PMTree(const std::vector<char>& elements);
  ~PMTree() = default;
  const Node* getRoot() const { return root.get(); }
  size_t countPermutations() const;

 private:
  std::unique_ptr<Node> root;
  void buildTree(Node* parent, const std::vector<char>& remainingElements);
  size_t countPermutationsHelper(const Node* node) const;
};
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
void runExperiment();
#endif  // INCLUDE_TREE_H_
