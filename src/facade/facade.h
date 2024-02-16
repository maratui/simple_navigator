#ifndef A2_SIMPLENAVIGATOR_FACADE_FACADE_H_
#define A2_SIMPLENAVIGATOR_FACADE_FACADE_H_

#include <string>
#include <vector>

#include "../graph.h"
#include "../graph_algorithms.h"

namespace s21 {
class Facade {
 public:
  void LoadGraphFromFile(const std::string &path);
  const std::vector<std::vector<unsigned>> &GetAdjacencyMatrix() const noexcept;

  const std::vector<unsigned> &DeepFirstSearch(unsigned start_vertex);
  const std::vector<unsigned> &BreadthFirstSearch(unsigned start_vertex);
  unsigned GetShortestPathBetweenVertices(unsigned vertex1, unsigned vertex2);
  const std::vector<std::vector<unsigned>>
      &GetShortestPathsBetweenAllVertices();
  const std::vector<std::vector<unsigned>> &GetLeastSpanningTree();
  const TsmResult &SolveTravelingSalesmanProblem();

 private:
  Graph graph_;
  GraphAlgorithms graph_algoriphms_;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_FACADE_FACADE_H_
