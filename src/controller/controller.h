#ifndef A2_SIMPLENAVIGATOR_CONTROLLER_CONTROLLER_H_
#define A2_SIMPLENAVIGATOR_CONTROLLER_CONTROLLER_H_

#include "../facade/facade.h"

namespace s21 {
class Controller {
 public:
  Controller() = delete;
  explicit Controller(Facade *facade);

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
  Facade *facade_{};
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_CONTROLLER_CONTROLLER_H_
