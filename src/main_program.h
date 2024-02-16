#ifndef A2_SIMPLENAVIGATOR_MAIN_PROGRAM_H_
#define A2_SIMPLENAVIGATOR_MAIN_PROGRAM_H_

#include <iostream>
#include <string>

#include "controller/controller.h"

namespace s21 {
class MainProgram {
 public:
  MainProgram() = delete;
  explicit MainProgram(Controller *controller);

  int Execute();

 private:
  static const std::string kQuit;

  void PrintLine();
  void PrintTitle();
  void PrintMenu();
  void ExecuteFunctions();
  void ExecuteLoadGraphFromFile();
  void ExecuteBreadthFirstSearch();
  void ExecuteDeepFirstSearch();
  void ExecuteGetShortestPathBetweenVertices();
  void ExecuteGetShortestPathsBetweenAllVertices();
  void ExecuteGetLeastSpanningTree();
  void ExecuteSolveTravelingSalesmanProblem();
  unsigned GetUnsignedFromString(const std::string &num_str);
  unsigned GetUnsignedFromStdin();
  void PrintMatrix();
  void PrintVector(char delimiter);

  Controller *controller_{};
  std::vector<std::vector<unsigned>> matrix_;
  std::vector<unsigned> vector_;
  std::string path_{};
  std::string entered_character_{};
  unsigned vertex_{};
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_MAIN_PROGRAM_H_
