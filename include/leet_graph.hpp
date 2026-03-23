/** Leet code style graph impl
 *  Remember how to represent these graphs...
 *  Adjacency Matrix: An VxE 2d array (matrix) where arr[i][j] == connection b/w
 * vertecies i and j.
 */

#pragma once
#include <vector>
#include <print>

class Node {
 public:
  int val;
  std::vector<Node*> neighbors;
  Node() {
    val = 0;
    neighbors = {};
  }

  explicit Node(int val) {
    this->val = val;
    neighbors = {};
  }

  Node(int val, std::vector<Node*> neighbors) {
    this->val = val;
    this->neighbors = neighbors;
  }
};

static std::vector<Node*> helper(Node* root, std::vector<Node*> buffer) {
  if (root == nullptr) return buffer;
  for (Node* peer : root->neighbors) {
    helper(peer, buffer);
  }
  buffer.push_back(root);
  printf("%d, ", root->val);
  return buffer;
}

// TODO could i do some sicp style stuff here?
// return some lambda that does this iteratively? std::iterator?
// How to keep track of state between iterations?
static std::vector<Node*> dfs_traversal(Node* root) {
  std::vector<Node*> buffer;
  return helper(root, buffer);
}
