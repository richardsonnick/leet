#include <gtest/gtest.h>

#include <cstdio>
#include <memory>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"
#include "leet_graph.hpp"

// gtest blocks stdout flush idk y :(
[[maybe_unused]]
static void print(std::string s) {
  printf("%s", s.c_str());
  fflush(stdout);
}

struct NodeDesciption {
  int val;
  // Stores a (hopefully) unique id for a Node's neighbor
  // TODO: Make this a set or something bozo
  std::vector<int> neigborIds;
};

class GraphUtilTest : public testing::Test {
 protected:
  std::vector<std::unique_ptr<Node<int>>> nodes;
  std::unordered_map<int, Node<int>*> nodeMap;

  void SetUp() override {}
  void TearDown() override {}

  // The graph is represented as a map: {node_id, NodeDesciption}
  Node<int>* buildGraph(std::unordered_map<int, NodeDesciption> adjacency) {
    for (auto& [node_id, _] : adjacency) {
      std::unique_ptr<Node<int>> new_node =
          std::make_unique<Node<int>>(node_id);
      nodeMap[node_id] = new_node.get();
      nodes.push_back(std::move(new_node));
    }
    for (auto& [node_id, node_description] : adjacency) {
      for (auto& neighbor_id : node_description.neigborIds) {
        nodeMap[node_id]->neighbors.push_back(nodeMap[neighbor_id]);
      }
    }
    return nodes.at(nodes.size() - 1).get();
  }
};

TEST_F(GraphUtilTest, TestDFSTraversal) {
  Node<int>* root = buildGraph({
      {{0}, {.val = 0, .neigborIds = {1, 2}}},
      {{1}, {.val = 1, .neigborIds = {4}}},
      {{2}, {.val = 2, .neigborIds = {3}}},
      {{3}, {.val = 3, .neigborIds = {}}},
      {{4}, {.val = 4, .neigborIds = {5}}},
      {{5}, {.val = 5, .neigborIds = {}}},
  });
  auto dfs_v = dfs_traversal(root);

  std::vector<int> expected = {5, 4, 1, 3, 2, 0};
  ASSERT_GE(dfs_v.size(), expected.size());
  EXPECT_EQ(dfs_v.size(), expected.size());
  for (int i = 0; i < dfs_v.size(); i++) {
    EXPECT_EQ(dfs_v.at(i)->val, expected[i]);
  }
}
