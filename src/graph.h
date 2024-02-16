#ifndef A2_SIMPLENAVIGATOR_GRAPH_H_
#define A2_SIMPLENAVIGATOR_GRAPH_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class Graph {
 public:
  void LoadGraphFromFile(const std::string &path);
  void ExportGraphToDot(const std::string &path);
  unsigned GetSize() const noexcept;
  unsigned GetWeight(unsigned raw, unsigned col) const noexcept;
  const std::vector<std::vector<unsigned>> &GetAdjacencyMatrix() const noexcept;

 private:
  void ReadSize(std::ifstream &in);
  void ReadAdjacencyMatrix(std::ifstream &in);
  unsigned GetUnsignedFromLine(std::istringstream &line_iss);
  std::string GetGraphName(const std::string &path) noexcept;
  void WriteAdjacencyMatrixToDot(std::ofstream &out);

  std::vector<std::vector<unsigned>> adjacency_matrix_;
  unsigned size_{};
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_GRAPH_H_
