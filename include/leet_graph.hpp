/** Leet code style graph impl
 *  Remember how to represent these graphs...
 *  Adjacency Matrix: An VxE 2d array (matrix) where arr[i][j] == connection b/w
 * vertecies i and j.
 */

#pragma once
#include <vector>
#include <print>

template<typename T>
class Node {
 public:
  int val;
  std::vector<Node<T>*> neighbors;
  Node() {
    val = 0;
    neighbors = {};
  }

  explicit Node<T>(int val) {
    this->val = val;
    neighbors = {};
  }

  Node<T>(int val, std::vector<Node<T>*> neighbors) {
    this->val = val;
    this->neighbors = neighbors;
  }
};

template<typename T>
static Node<T>* helper(Node<T>* root, std::vector<Node<T>*>& buffer) {
  if (root == nullptr) return root;
  for (Node<T>* peer : root->neighbors) {
    helper(peer, buffer);
  }
  buffer.push_back(root);
  return root;
}

// TODO could i do some sicp style stuff here?
// return some lambda that does this iteratively? std::iterator?
// How to keep track of state between iterations?
template<typename T>
static std::vector<Node<T>*> dfs_traversal(Node<T>* root) {
  std::vector<Node<T>*> buffer;
  helper(root, buffer);
  return buffer;
}
