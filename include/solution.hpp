#include "leet_graph.hpp"

class ISolution {
 public:
  virtual void run() = 0;
  virtual ~ISolution() = default;
};

class CloneGraph : public ISolution {
 private:
  struct Input {Node* node;};
  struct Output {Node* node;};
  Input in;
  Output out;

 public:
  CloneGraph(Input in) : in(in) {}
  void run() override;
  Output result() { return out; }
};
