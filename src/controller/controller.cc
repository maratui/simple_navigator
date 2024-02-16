#include "controller.h"

using namespace s21;

Controller::Controller(Facade *facade) : facade_(facade) {}

void Controller::LoadGraphFromFile(const std::string &path) {
  facade_->LoadGraphFromFile(path);
}

const std::vector<std::vector<unsigned>> &Controller::GetAdjacencyMatrix()
    const noexcept {
  return facade_->GetAdjacencyMatrix();
}

const std::vector<unsigned> &Controller::DeepFirstSearch(
    unsigned start_vertex) {
  return facade_->DeepFirstSearch(start_vertex);
}

const std::vector<unsigned> &Controller::BreadthFirstSearch(
    unsigned start_vertex) {
  return facade_->BreadthFirstSearch(start_vertex);
}

unsigned Controller::GetShortestPathBetweenVertices(unsigned vertex1,
                                                    unsigned vertex2) {
  return facade_->GetShortestPathBetweenVertices(vertex1, vertex2);
}

const std::vector<std::vector<unsigned>>
    &Controller::GetShortestPathsBetweenAllVertices() {
  return facade_->GetShortestPathsBetweenAllVertices();
}

const std::vector<std::vector<unsigned>> &Controller::GetLeastSpanningTree() {
  return facade_->GetLeastSpanningTree();
}

const TsmResult &Controller::SolveTravelingSalesmanProblem() {
  return facade_->SolveTravelingSalesmanProblem();
}
