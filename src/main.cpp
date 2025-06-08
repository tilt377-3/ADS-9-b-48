// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
int main() {
  std::vector<char> in = { '1','2','3' };
  PMTree tree(in);
  
  std::cout << "All permutations:\n";
  auto allPerms = getAllPerms(tree);
  for (const auto& perm : allPerms) {
    for (char c : perm) std::cout << c;
    std::cout << "\n";
  }
  
  std::cout << "\nPermutation 1: ";
  auto perm1 = getPerm1(tree, 1);
  for (char c : perm1) std::cout << c;
  std::cout << "\n";
  
  std::cout << "Permutation 2: ";
  auto perm2 = getPerm2(tree, 2);
  for (char c : perm2) std::cout << c;
  std::cout << "\n";
  
  std::cout << "\nRunning experiment...\n";
  runExperiment();
  
  return 0;
}
