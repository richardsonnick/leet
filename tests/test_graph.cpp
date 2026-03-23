#include <gtest/gtest.h>

#include <cstdio>
#include <memory>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"
#include "leet_graph.hpp"

// gtest blocks stdout flush idk y :(
static void print(std::string s) {
  printf("%s", s.c_str());
  fflush(stdout);
}

struct NodeDesciption {
  int val;
  std::vector<int>
      neigborIds;  // Stores a (hopefully) unique id for a Node's neighbor
};

class GraphUtilTest : public testing::Test {
 protected:
  std::vector<std::unique_ptr<Node>> nodes;
  std::unordered_map<int, Node*> nodeMap;

  void SetUp() override {}
  void TearDown() override {}

  // The graph is represented as a map: {node_id, NodeDesciption}
  Node* buildGraph(std::unordered_map<int, NodeDesciption> adjacency) {
    for (auto& [node_id, _] : adjacency) {
      std::unique_ptr<Node> new_node = std::make_unique<Node>(node_id);
      nodeMap[node_id] = new_node.get();
      nodes.push_back(std::move(new_node));
    }
    for (auto& [node_id, node_description] : adjacency) {
      for (auto& neighbor_id : node_description.neigborIds) {
        print(std::format("id: {}\n", node_id));
        nodeMap[node_id]->neighbors.push_back(nodeMap[neighbor_id]);
      }
    }
    return nodeMap[adjacency.begin()->first];
  }
};

TEST_F(GraphUtilTest, TestDFSTraversal) {
  Node* root = buildGraph({
      {{0}, {.val = 0, .neigborIds = {1, 2}}},
      {{1}, {.val = 1, .neigborIds = {3, 4}}},
      {{2}, {.val = 2, .neigborIds = {3}}},
      {{3}, {.val = 3, .neigborIds = {}}},
      {{4}, {.val = 4, .neigborIds = {5}}},
      {{5}, {.val = 5, .neigborIds = {}}},
  });
  auto dfs_v = dfs_traversal(root);

  std::vector<int> expected = {5, 4, 3, 2, 1, 0};
  for (int i = 0; i < dfs_v.size(); i++) {
    EXPECT_EQ(dfs_v.at(i)->val, expected[i]);
  }

  EXPECT_EQ(dfs_v.size(), expected.size());
}
