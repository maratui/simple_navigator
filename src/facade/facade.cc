#include "facade.h"

using namespace s21;

void Facade::LoadGraphFromFile(const std::string &path) {
  graph_.LoadGraphFromFile(path);
}

const std::vector<std::vector<unsigned>> &Facade::GetAdjacencyMatrix()
    const noexcept {
  return graph_.GetAdjacencyMatrix();
}

const std::vector<unsigned> &Facade::DeepFirstSearch(unsigned start_vertex) {
  return graph_algoriphms_.DeepFirstSearch(graph_, start_vertex);
}

const std::vector<unsigned> &Facade::BreadthFirstSearch(unsigned start_vertex) {
  return graph_algoriphms_.BreadthFirstSearch(graph_, start_vertex);
}

unsigned Facade::GetShortestPathBetweenVertices(unsigned vertex1,
                                                unsigned vertex2) {
  return graph_algoriphms_.GetShortestPathBetweenVertices(graph_, vertex1,
                                                          vertex2);
}

const std::vector<std::vector<unsigned>>
    &Facade::GetShortestPathsBetweenAllVertices() {
  return graph_algoriphms_.GetShortestPathsBetweenAllVertices(graph_);
}

const std::vector<std::vector<unsigned>> &Facade::GetLeastSpanningTree() {
  return graph_algoriphms_.GetLeastSpanningTree(graph_);
}

const TsmResult &Facade::SolveTravelingSalesmanProblem() {
  return graph_algoriphms_.SolveTravelingSalesmanProblem(graph_);
}
