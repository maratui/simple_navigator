#ifndef A2_SIMPLENAVIGATOR_TESTS_TESTS_H_
#define A2_SIMPLENAVIGATOR_TESTS_TESTS_H_

#include <gtest/gtest.h>

#include <iostream>

#include "../graph.h"
#include "../graph_algorithms.h"
#include "../tsm_result.h"

namespace s21 {
class GraphTester : protected Graph {
 public:
  using Graph::ExportGraphToDot;
  using Graph::GetAdjacencyMatrix;
  using Graph::LoadGraphFromFile;
};

class GraphAlgorithmsTester : protected GraphAlgorithms {
 public:
  using GraphAlgorithms::BreadthFirstSearch;
  using GraphAlgorithms::DeepFirstSearch;
  using GraphAlgorithms::GetLeastSpanningTree;
  using GraphAlgorithms::GetShortestPathBetweenVertices;
  using GraphAlgorithms::GetShortestPathsBetweenAllVertices;
  using GraphAlgorithms::SolveTravelingSalesmanProblem;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_TESTS_TESTS_H_
