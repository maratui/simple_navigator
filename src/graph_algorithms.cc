#include "graph_algorithms.h"

using namespace s21;

const std::vector<unsigned> &GraphAlgorithms::DeepFirstSearch(
    const Graph &graph, unsigned start_vertex) {
  adaptor_ = &stack_;

  return FirstSearch(graph, start_vertex);
}

const std::vector<unsigned> &GraphAlgorithms::BreadthFirstSearch(
    const Graph &graph, unsigned start_vertex) {
  adaptor_ = &queue_;

  return FirstSearch(graph, start_vertex);
}

const std::vector<unsigned> &GraphAlgorithms::FirstSearch(
    const Graph &graph, unsigned start_vertex) {
  traversed_vertices_.clear();
  if ((start_vertex > 0) && (start_vertex <= graph.GetSize())) {
    InitIsUsed(graph, start_vertex);
    traversed_vertices_.push_back(start_vertex);
    adaptor_->Init();
    PushAdjacencyVertices(graph, start_vertex);

    while (adaptor_->Empty() == false) {
      unsigned vertex = adaptor_->Pop();

      while ((adaptor_->Empty() == false) && (is_used_[vertex] == true)) {
        vertex = adaptor_->Pop();
      }
      if (is_used_[vertex] == false) {
        traversed_vertices_.push_back(vertex);
        is_used_[vertex] = true;
        PushAdjacencyVertices(graph, vertex);
      }
    }
  }

  return traversed_vertices_;
}

void GraphAlgorithms::InitIsUsed(const Graph &graph, unsigned start_vertex) {
  is_used_.assign(graph.GetSize() + 1U, false);
  is_used_[start_vertex] = true;
}

void GraphAlgorithms::PushAdjacencyVertices(const Graph &graph,
                                            unsigned vertex) {
  const unsigned kSize = graph.GetSize() + 1U;

  for (auto adjacency_vertex = 1U; adjacency_vertex < kSize;
       adjacency_vertex++) {
    if ((graph.GetWeight(vertex, adjacency_vertex) != 0U) &&
        (is_used_[adjacency_vertex] == false)) {
      adaptor_->Push(adjacency_vertex);
    }
  }
}

unsigned GraphAlgorithms::GetShortestPathBetweenVertices(const Graph &graph,
                                                         unsigned vertex1,
                                                         unsigned vertex2) {
  unsigned result{};
  if (((vertex1 > 0) && (vertex1 <= graph.GetSize())) &&
      ((vertex2 > 0) && (vertex2 <= graph.GetSize()))) {
    InitIsUsed(graph, vertex1);
    InitWeightsMatrix(graph);
    InitWeights(graph, vertex1);
    DijkstraAlgorithm(graph);
    result = weights_[vertex2];
  }

  return result;
}

void GraphAlgorithms::InitWeights(const Graph &graph, unsigned start_vertex) {
  const unsigned kSize = graph.GetSize() + 1U;

  weights_.assign(kSize, INT_MAX);
  for (auto j = 1U; j < kSize; j++) {
    weights_[j] = weights_matrix_[start_vertex][j];
  }
  weights_[start_vertex] = 0U;
}

void GraphAlgorithms::InitWeightsMatrix(const Graph &graph) {
  const unsigned kSize = graph.GetSize() + 1U;

  weights_.assign(kSize, INT_MAX);
  weights_matrix_.assign(kSize, weights_);
  for (auto i = 1U; i < kSize; i++) {
    for (auto j = 1U; j < kSize; j++) {
      unsigned weight = graph.GetWeight(i, j);

      if (weight > 0U) {
        weights_matrix_[i][j] = weight;
      }
      if (i == j) {
        weights_matrix_[i][j] = 0U;
      }
    }
  }
}

void GraphAlgorithms::DijkstraAlgorithm(const Graph &graph) {
  const unsigned kSize = graph.GetSize() + 1U;

  for (auto i = 1U; i < kSize; i++) {
    unsigned min_weight = INT_MAX;
    unsigned vertex = 0U;

    for (auto j = 1U; j < kSize; j++) {
      if ((is_used_[j] == false) && (weights_[j] < min_weight)) {
        min_weight = weights_[j];
        vertex = j;
      }
    }
    if (vertex > 0U) {
      is_used_[vertex] = true;
      for (auto j = 1U; j < kSize; j++) {
        if ((weights_[j] > (weights_[vertex] + weights_matrix_[vertex][j]))) {
          weights_[j] = weights_[vertex] + weights_matrix_[vertex][j];
        }
      }
    }
  }
}

const std::vector<std::vector<unsigned>>
    &GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph &graph) {
  const unsigned kSize = graph.GetSize() + 1U;

  InitWeightsMatrix(graph);
  for (auto k = 1U; k < kSize; k++) {
    for (auto i = 1U; i < kSize; i++) {
      for (auto j = 1U; j < kSize; j++) {
        if (weights_matrix_[i][j] >
            (weights_matrix_[i][k] + weights_matrix_[k][j])) {
          weights_matrix_[i][j] = weights_matrix_[i][k] + weights_matrix_[k][j];
        }
      }
    }
  }
  WeightsMatrixToAdjacencyMatrix();

  return weights_matrix_;
}

void GraphAlgorithms::WeightsMatrixToAdjacencyMatrix() {
  if (weights_matrix_.size() > 0) {
    weights_matrix_.erase(weights_matrix_.begin());
  }
  if (weights_matrix_.size() > 0) {
    for (auto i = 0U; i < weights_matrix_[i].size(); i++) {
      weights_matrix_[i].erase(weights_matrix_[i].begin());
    }
  }
}

const std::vector<std::vector<unsigned>> &GraphAlgorithms::GetLeastSpanningTree(
    const Graph &graph) {
  const unsigned kSize = graph.GetSize() + 1U;

  InitLeastSpanningTree(graph);
  for (auto i = 1U; i < kSize; i++) {
    unsigned vertex = 0U;

    for (auto j = 1U; j < kSize; j++) {
      if ((is_used_[j] == false) &&
          ((vertex == 0U) || (weights_[j] < weights_[vertex]))) {
        vertex = j;
      }
    }
    if (vertex > 0U) {
      is_used_[vertex] = true;
      if (path_[vertex] > 0) {
        least_spanning_tree_[path_[vertex] - 1U][vertex - 1U] =
            weights_matrix_[path_[vertex]][vertex];
        least_spanning_tree_[vertex - 1U][path_[vertex] - 1U] =
            weights_matrix_[vertex][path_[vertex]];
      }
      for (auto j = 1U; j < kSize; j++) {
        if (weights_[j] > weights_matrix_[vertex][j]) {
          weights_[j] = weights_matrix_[vertex][j];
          path_[j] = vertex;
        }
      }
    }
  }

  return least_spanning_tree_;
}

void GraphAlgorithms::InitLeastSpanningTree(const Graph &graph) {
  const unsigned kSize = graph.GetSize() + 1U;
  std::vector<unsigned> unsigned_vector(kSize - 1U, 0U);

  least_spanning_tree_.assign(kSize - 1U, unsigned_vector);
  path_.assign(kSize, 0U);
  is_used_.assign(kSize, false);
  InitWeightsMatrix(graph);
  weights_.assign(kSize, INT_MAX);
  weights_[1U] = 0U;
}

const TsmResult &GraphAlgorithms::SolveTravelingSalesmanProblem(
    const Graph &graph) {
  std::vector<std::vector<double>> distances;

  distances.assign(graph.GetSize(), std::vector<double>(graph.GetSize(), 0.0));
  for (auto i = 0U; i < distances.size(); i++) {
    for (auto j = 0U; j < distances[i].size(); j++) {
      if (i == j) {
        distances[i][j] = 0.0;
      } else {
        distances[i][j] = (double)graph.GetWeight(i + 1U, j + 1U);
      }
    }
  }

  AntColony ant_colony(distances, 30U);
  ant_colony.Run();

  tsm_result_.vertices = ant_colony.GetBestAntPaths();
  for (auto j = 0U; j < tsm_result_.vertices.size(); j++) {
    tsm_result_.vertices[j] += 1U;
  }
  tsm_result_.distance = ant_colony.GetMinDistance();

  return tsm_result_;
}
