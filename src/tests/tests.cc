#include "tests.h"

TEST(TestGraph, LoadGraphFromFile) {
  s21::GraphTester graph_tester;
  std::vector<std::vector<unsigned>> adjacency_matrix;

  graph_tester.LoadGraphFromFile("../tests/graph");
  adjacency_matrix = graph_tester.GetAdjacencyMatrix();

  EXPECT_EQ(6, adjacency_matrix.size());
  EXPECT_EQ(6, adjacency_matrix[0].size());

  EXPECT_EQ(0, adjacency_matrix[0][0]);
  EXPECT_EQ(7, adjacency_matrix[0][1]);
  EXPECT_EQ(9, adjacency_matrix[0][2]);
  EXPECT_EQ(0, adjacency_matrix[0][3]);
  EXPECT_EQ(0, adjacency_matrix[0][4]);
  EXPECT_EQ(14, adjacency_matrix[0][5]);

  EXPECT_EQ(7, adjacency_matrix[1][0]);
  EXPECT_EQ(0, adjacency_matrix[1][1]);
  EXPECT_EQ(10, adjacency_matrix[1][2]);
  EXPECT_EQ(15, adjacency_matrix[1][3]);
  EXPECT_EQ(0, adjacency_matrix[1][4]);
  EXPECT_EQ(0, adjacency_matrix[1][5]);

  EXPECT_EQ(9, adjacency_matrix[2][0]);
  EXPECT_EQ(10, adjacency_matrix[2][1]);
  EXPECT_EQ(0, adjacency_matrix[2][2]);
  EXPECT_EQ(11, adjacency_matrix[2][3]);
  EXPECT_EQ(0, adjacency_matrix[2][4]);
  EXPECT_EQ(2, adjacency_matrix[2][5]);

  EXPECT_EQ(0, adjacency_matrix[3][0]);
  EXPECT_EQ(15, adjacency_matrix[3][1]);
  EXPECT_EQ(11, adjacency_matrix[3][2]);
  EXPECT_EQ(0, adjacency_matrix[3][3]);
  EXPECT_EQ(6, adjacency_matrix[3][4]);
  EXPECT_EQ(0, adjacency_matrix[3][5]);

  EXPECT_EQ(0, adjacency_matrix[4][0]);
  EXPECT_EQ(0, adjacency_matrix[4][1]);
  EXPECT_EQ(0, adjacency_matrix[4][2]);
  EXPECT_EQ(6, adjacency_matrix[4][3]);
  EXPECT_EQ(0, adjacency_matrix[4][4]);
  EXPECT_EQ(9, adjacency_matrix[4][5]);

  EXPECT_EQ(14, adjacency_matrix[5][0]);
  EXPECT_EQ(0, adjacency_matrix[5][1]);
  EXPECT_EQ(2, adjacency_matrix[5][2]);
  EXPECT_EQ(0, adjacency_matrix[5][3]);
  EXPECT_EQ(9, adjacency_matrix[5][4]);
  EXPECT_EQ(0, adjacency_matrix[5][5]);
}

TEST(TestGraph, ExportGraphToDot) {
  s21::GraphTester graph_tester;
  std::vector<std::vector<unsigned>> adjacency_matrix_1;
  std::vector<std::vector<unsigned>> adjacency_matrix_2;

  graph_tester.LoadGraphFromFile("../tests/graph");
  adjacency_matrix_1 = graph_tester.GetAdjacencyMatrix();

  graph_tester.ExportGraphToDot("../tests/export_graph.dot");
}

TEST(TestGraphAlgorithms, DeepFirstSearch) {
  s21::Graph graph;
  s21::GraphAlgorithmsTester graph_algorithms_tester;
  std::vector<unsigned> traversed_vertices;

  graph.LoadGraphFromFile("../tests/graph");
  traversed_vertices = graph_algorithms_tester.DeepFirstSearch(graph, 1);

  EXPECT_EQ(6, traversed_vertices.size());
  EXPECT_EQ(1, traversed_vertices[0]);
  EXPECT_EQ(6, traversed_vertices[1]);
  EXPECT_EQ(5, traversed_vertices[2]);
  EXPECT_EQ(4, traversed_vertices[3]);
  EXPECT_EQ(3, traversed_vertices[4]);
  EXPECT_EQ(2, traversed_vertices[5]);

  graph.LoadGraphFromFile("../tests/graph_5");
  traversed_vertices = graph_algorithms_tester.DeepFirstSearch(graph, 2);

  EXPECT_EQ(5, traversed_vertices.size());
  EXPECT_EQ(2, traversed_vertices[0]);
  EXPECT_EQ(5, traversed_vertices[1]);
  EXPECT_EQ(1, traversed_vertices[2]);
  EXPECT_EQ(4, traversed_vertices[3]);
  EXPECT_EQ(3, traversed_vertices[4]);
}

TEST(TestGraphAlgorithms, BreadthFirstSearch) {
  s21::Graph graph;
  s21::GraphAlgorithmsTester graph_algorithms_tester;
  std::vector<unsigned> traversed_vertices;

  graph.LoadGraphFromFile("../tests/graph");
  traversed_vertices = graph_algorithms_tester.BreadthFirstSearch(graph, 1);

  EXPECT_EQ(6, traversed_vertices.size());
  EXPECT_EQ(1, traversed_vertices[0]);
  EXPECT_EQ(2, traversed_vertices[1]);
  EXPECT_EQ(3, traversed_vertices[2]);
  EXPECT_EQ(6, traversed_vertices[3]);
  EXPECT_EQ(4, traversed_vertices[4]);
  EXPECT_EQ(5, traversed_vertices[5]);

  graph.LoadGraphFromFile("../tests/graph_5");
  traversed_vertices = graph_algorithms_tester.BreadthFirstSearch(graph, 2);

  EXPECT_EQ(5, traversed_vertices.size());
  EXPECT_EQ(2, traversed_vertices[0]);
  EXPECT_EQ(1, traversed_vertices[1]);
  EXPECT_EQ(5, traversed_vertices[2]);
  EXPECT_EQ(3, traversed_vertices[3]);
  EXPECT_EQ(4, traversed_vertices[4]);
}

TEST(TestGraphAlgorithms, GetShortestPathBetweenVertices) {
  s21::Graph graph;
  s21::GraphAlgorithmsTester graph_algorithms_tester;
  unsigned weight{};

  graph.LoadGraphFromFile("../tests/graph");
  weight = graph_algorithms_tester.GetShortestPathBetweenVertices(graph, 1, 1);
  EXPECT_EQ(0, weight);
  weight = graph_algorithms_tester.GetShortestPathBetweenVertices(graph, 1, 2);
  EXPECT_EQ(7, weight);
  weight = graph_algorithms_tester.GetShortestPathBetweenVertices(graph, 1, 3);
  EXPECT_EQ(9, weight);
  weight = graph_algorithms_tester.GetShortestPathBetweenVertices(graph, 1, 4);
  EXPECT_EQ(20, weight);
  weight = graph_algorithms_tester.GetShortestPathBetweenVertices(graph, 1, 5);
  EXPECT_EQ(20, weight);
  weight = graph_algorithms_tester.GetShortestPathBetweenVertices(graph, 1, 6);
  EXPECT_EQ(11, weight);
}

TEST(TestGraphAlgorithms, GetShortestPathsBetweenAllVertices) {
  s21::Graph graph;
  s21::GraphAlgorithmsTester graph_algorithms_tester;
  std::vector<std::vector<unsigned>> weights_matrix;

  graph.LoadGraphFromFile("../tests/graph");
  weights_matrix =
      graph_algorithms_tester.GetShortestPathsBetweenAllVertices(graph);

  EXPECT_EQ(0, weights_matrix[0][0]);
  EXPECT_EQ(7, weights_matrix[0][1]);
  EXPECT_EQ(9, weights_matrix[0][2]);
  EXPECT_EQ(20, weights_matrix[0][3]);
  EXPECT_EQ(20, weights_matrix[0][4]);
  EXPECT_EQ(11, weights_matrix[0][5]);

  EXPECT_EQ(0, weights_matrix[0][0]);
  EXPECT_EQ(7, weights_matrix[1][0]);
  EXPECT_EQ(9, weights_matrix[2][0]);
  EXPECT_EQ(20, weights_matrix[3][0]);
  EXPECT_EQ(20, weights_matrix[4][0]);
  EXPECT_EQ(11, weights_matrix[5][0]);

  weights_matrix = graph_algorithms_tester.GetLeastSpanningTree(graph);

  EXPECT_EQ(0, weights_matrix[0][0]);
  EXPECT_EQ(7, weights_matrix[0][1]);
  EXPECT_EQ(9, weights_matrix[0][2]);
  EXPECT_EQ(0, weights_matrix[0][3]);
  EXPECT_EQ(0, weights_matrix[0][4]);
  EXPECT_EQ(0, weights_matrix[0][5]);

  EXPECT_EQ(7, weights_matrix[1][0]);
  EXPECT_EQ(0, weights_matrix[1][1]);
  EXPECT_EQ(0, weights_matrix[1][2]);
  EXPECT_EQ(0, weights_matrix[1][3]);
  EXPECT_EQ(0, weights_matrix[1][4]);
  EXPECT_EQ(0, weights_matrix[1][5]);

  EXPECT_EQ(9, weights_matrix[2][0]);
  EXPECT_EQ(0, weights_matrix[2][1]);
  EXPECT_EQ(0, weights_matrix[2][2]);
  EXPECT_EQ(0, weights_matrix[2][3]);
  EXPECT_EQ(0, weights_matrix[2][4]);
  EXPECT_EQ(2, weights_matrix[2][5]);

  EXPECT_EQ(0, weights_matrix[3][0]);
  EXPECT_EQ(0, weights_matrix[3][1]);
  EXPECT_EQ(0, weights_matrix[3][2]);
  EXPECT_EQ(0, weights_matrix[3][3]);
  EXPECT_EQ(6, weights_matrix[3][4]);
  EXPECT_EQ(0, weights_matrix[3][5]);

  EXPECT_EQ(0, weights_matrix[4][0]);
  EXPECT_EQ(0, weights_matrix[4][1]);
  EXPECT_EQ(0, weights_matrix[4][2]);
  EXPECT_EQ(6, weights_matrix[4][3]);
  EXPECT_EQ(0, weights_matrix[4][4]);
  EXPECT_EQ(9, weights_matrix[4][5]);

  EXPECT_EQ(0, weights_matrix[5][0]);
  EXPECT_EQ(0, weights_matrix[5][1]);
  EXPECT_EQ(2, weights_matrix[5][2]);
  EXPECT_EQ(0, weights_matrix[5][3]);
  EXPECT_EQ(9, weights_matrix[5][4]);
  EXPECT_EQ(0, weights_matrix[5][5]);
}

TEST(TestGraphAlgorithms, SolveTravelingSalesmanProblem) {
  s21::Graph graph;
  s21::GraphAlgorithmsTester graph_algorithms_tester;
  s21::TsmResult tsm_result;
  double distance{};
  unsigned vertex{};

  graph.LoadGraphFromFile("../tests/graph");
  tsm_result = graph_algorithms_tester.SolveTravelingSalesmanProblem(graph);

  distance = 0.0;
  vertex = tsm_result.vertices[0];
  for (auto j = 0U; j < tsm_result.vertices.size(); j++) {
    distance += (double)graph.GetWeight(vertex, tsm_result.vertices[j]);
    vertex = tsm_result.vertices[j];
  }
  EXPECT_EQ(distance, tsm_result.distance);

  graph.LoadGraphFromFile("../tests/bad_graph");
  tsm_result = graph_algorithms_tester.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(0, tsm_result.vertices.size());
}
