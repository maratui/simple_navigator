#ifndef A2_SIMPLENAVIGATOR_GRAPH_ALGORITHMS_H_
#define A2_SIMPLENAVIGATOR_GRAPH_ALGORITHMS_H_

#include <climits>
#include <vector>

#include "adaptors/queue.h"
#include "adaptors/stack.h"
#include "ant_colony/ant_colony.h"
#include "graph.h"
#include "tsm_result.h"

namespace s21 {
class GraphAlgorithms {
 public:
  const std::vector<unsigned> &DeepFirstSearch(const Graph &graph,
                                               unsigned start_vertex);
  const std::vector<unsigned> &BreadthFirstSearch(const Graph &graph,
                                                  unsigned start_vertex);
  unsigned GetShortestPathBetweenVertices(const Graph &graph, unsigned vertex1,
                                          unsigned vertex2);
  const std::vector<std::vector<unsigned>> &GetShortestPathsBetweenAllVertices(
      const Graph &graph);
  const std::vector<std::vector<unsigned>> &GetLeastSpanningTree(
      const Graph &graph);
  const TsmResult &SolveTravelingSalesmanProblem(const Graph &graph);

 private:
  const std::vector<unsigned> &FirstSearch(const Graph &graph,
                                           unsigned start_vertex);
  void InitIsUsed(const Graph &graph, unsigned start_vertex);
  void PushAdjacencyVertices(const Graph &graph, unsigned vertex);
  void InitWeightsMatrix(const Graph &graph);
  void InitWeights(const Graph &graph, unsigned start_vertex);
  void DijkstraAlgorithm(const Graph &graph);
  void WeightsMatrixToAdjacencyMatrix();
  void InitLeastSpanningTree(const Graph &graph);

  std::vector<bool> is_used_;

  std::vector<unsigned> traversed_vertices_;
  Adaptor *adaptor_ = nullptr;
  Stack stack_;
  Queue queue_;

  std::vector<std::vector<unsigned>> weights_matrix_;
  std::vector<unsigned> weights_;

  std::vector<std::vector<unsigned>> least_spanning_tree_;
  std::vector<unsigned> path_;

  TsmResult tsm_result_{};
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_GRAPH_ALGORITHMS_H_
