// Copyright 2022 NNTU-CS
#include  <iostream>
#include <algorithm>
#include  <fstream>
#include <random>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
PMTree::PMTree(const std::vector<char>& elements) {
  if (elements.empty()) {
    root = nullptr;
    return;
  }
  root = std::make_unique<Node>('\0');
  buildTree(root.get(), elements);
}

void PMTree::buildTree(Node* parent, const std::vector<char>& remainingElements) {
  if (remainingElements.empty()) {
    return;
  }
  for (size_t i = 0; i < remainingElements.size(); ++i) {
    parent->children.emplace_back(std::make_unique<Node>(remainingElements[i]));
    Node* child = parent->children.back().get();
    std::vector<char> newRemaining;
    newRemaining.reserve(remainingElements.size() - 1);
    for (size_t j = 0; j < remainingElements.size(); ++j) {
      if (j != i) {
        newRemaining.push_back(remainingElements[j]);
      }
    }
    buildTree(child, newRemaining);
  }
}

size_t PMTree::countPermutationsHelper(const Node* node) const {
  if (!node) return 0;
  if (node->children.empty()) return 1;
  size_t count = 0;
  for (const auto& child : node->children) {
    count += countPermutationsHelper(child.get());
  }
  return count;
}

size_t PMTree::countPermutations() const {
  return countPermutationsHelper(root.get());
}

void collectPermutations(const PMTree::Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) {
  if (!node) return;
  if (node->value != '\0') {
    current.push_back(node->value);
  }
  if (node->children.empty() && !current.empty()) {
    result.push_back(current);
  }
  for (const auto& child : node->children) {
    collectPermutations(child.get(), current, result);
  }
  if (node->value != '\0') {
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  collectPermutations(tree.getRoot(), current, result);
  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  if (num < 1) return {};
  std::vector<std::vector<char>> allPerms = getAllPerms(tree);
  if (static_cast<size_t>(num) > allPerms.size()) {
    return {};
  }
  return allPerms[num - 1];
}

bool getPermHelper(const PMTree::Node* node, int& remaining, std::vector<char>& result) {
  if (!node) return false;
  if (node->value != '\0') {
    result.push_back(node->value);
  }
  if (node->children.empty()) {
    if (--remaining == 0) {
      return true;
    }
    if (node->value != '\0') {
      result.pop_back();
    }
    return false;
  }
  for (const auto& child : node->children) {
    if (getPermHelper(child.get(), remaining, result)) {
      return true;
    }
  }
  if (node->value != '\0') {
    result.pop_back();
  }
  return false;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (num < 1) return {};
  std::vector<char> result;
  int remaining = num;
  if (getPermHelper(tree.getRoot(), remaining, result)) {
    return result;
  }
  return {};
}

void runExperiment() {
  const std::vector<int> sizes = { 1, 2, 3, 4, 5, 6, 7, 8 };
  std::ofstream results("experiment_results.csv");
  results << "n,getAllPerms,getPerm1,getPerm2\n";
  
  for (int n : sizes) {
    std::vector<char> in;
    for (int i = 0; i < n; ++i) {
      in.push_back('1' + i);
    }
    
    PMTree tree(in);
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    double duration_all = std::chrono::duration<double>(end - start).count();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, static_cast<int>(perms.size()));
    int random_index = dist(gen);
    
    start = std::chrono::high_resolution_clock::now();
    std::vector<char> result1 = getPerm1(tree, random_index);
    end = std::chrono::high_resolution_clock::now();
    double duration1 = std::chrono::duration<double>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    std::vector<char> result2 = getPerm2(tree, random_index);
    end = std::chrono::high_resolution_clock::now();
    double duration2 = std::chrono::duration<double>(end - start).count();
    
    results << n << ","
      << duration_all << ","
      << duration1 << ","
      << duration2 << "\n";
  }

  results.close();
}
