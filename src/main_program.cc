#include "main_program.h"

using namespace s21;

const std::string MainProgram::kQuit = "q";

MainProgram::MainProgram(Controller *controller) : controller_(controller) {}

int MainProgram::Execute() {
  PrintTitle();
  while (entered_character_ != kQuit) {
    PrintMenu();
    std::cin >> entered_character_;
    ExecuteFunctions();
    if (entered_character_ == kQuit) {
      std::cout << "bye";
    } else {
      std::cout << "To continue, press the key \"Enter\"";
      std::cin.get();
      std::cin.get();
    }
  }
  PrintLine();

  return 0;
}

void MainProgram::PrintLine() {
  std::cout << "\n-------------------------------------------------------------"
               "---------\n";
}

void MainProgram::PrintTitle() {
  PrintLine();
  std::cout << "     This is the console application for testing the "
               "functionality of \n the implemented s21_graph.h and "
               "s21_graph_algorithms.h libraries.";
}

void MainProgram::PrintMenu() {
  PrintLine();
  std::cout
      << " 1 - loading the original graph from a file;\n"
         " 2 - graph traversal in breadth with output of the result to the "
         "console;\n"
         " 3 - graph traversal in depth with output of the result to the "
         "console;\n"
         " 4 - searching for the shortest path between any two vertices and\n"
         "     displaying the result to the console;\n"
         " 5 - searching for the shortest paths between all pairs of vertices\n"
         "     in the graph with the output of the resulting matrix to the "
         "console;\n"
         " 6 - searching for the minimal spanning tree in the graph with\n"
         "     the output of the resulting adjacency matrix to the console;\n"
         " 7 - solving the salesman problem with the output of\n"
         "     the resulting route and its length to the console.\n"
         " q - quit.";
  PrintLine();
}

void MainProgram::ExecuteFunctions() {
  unsigned query_num = GetUnsignedFromString(entered_character_);

  if (query_num == 1) {
    ExecuteLoadGraphFromFile();
  } else if (query_num == 2) {
    ExecuteBreadthFirstSearch();
  } else if (query_num == 3) {
    ExecuteDeepFirstSearch();
  } else if (query_num == 4) {
    ExecuteGetShortestPathBetweenVertices();
  } else if (query_num == 5) {
    ExecuteGetShortestPathsBetweenAllVertices();
  } else if (query_num == 6) {
    ExecuteGetLeastSpanningTree();
  } else if (query_num == 7) {
    ExecuteSolveTravelingSalesmanProblem();
  }
}

void MainProgram::ExecuteLoadGraphFromFile() {
  std::cout << "Enter the path to the file of the graph: ";
  std::cin >> path_;
  controller_->LoadGraphFromFile(path_);
  std::cout << "The original graph from a file:\n";
  matrix_ = controller_->GetAdjacencyMatrix();
  PrintMatrix();
}

void MainProgram::ExecuteBreadthFirstSearch() {
  std::cout << "Enter the number start vertex: ";
  vertex_ = GetUnsignedFromStdin();
  std::cout << "The graph traversal in breadth: \n";
  if (matrix_.size() > 0 && ((vertex_ > 0) && (vertex_ <= matrix_.size()))) {
    vector_ = controller_->BreadthFirstSearch(vertex_);
    PrintVector(' ');
  }
}

void MainProgram::ExecuteDeepFirstSearch() {
  std::cout << "Enter the number start vertex: ";
  vertex_ = GetUnsignedFromStdin();
  std::cout << "The graph traversal in depth: \n";
  if (matrix_.size() > 0 && ((vertex_ > 0) && (vertex_ <= matrix_.size()))) {
    vector_ = controller_->DeepFirstSearch(vertex_);
    PrintVector(' ');
  }
}

void MainProgram::ExecuteGetShortestPathBetweenVertices() {
  unsigned vertex1{};
  unsigned vertex2{};

  std::cout << "Enter the number vertex1: ";
  vertex1 = GetUnsignedFromStdin();
  std::cout << "Enter the number vertex2: ";
  vertex2 = GetUnsignedFromStdin();
  std::cout << "The shortest path between two vertices: \n";
  if ((matrix_.size() > 0) && ((vertex1 > 0) && (vertex1 <= matrix_.size())) &&
      ((vertex2 > 0) && (vertex2 <= matrix_.size()))) {
    std::cout << controller_->GetShortestPathBetweenVertices(vertex1, vertex2)
              << "\n";
  }
}

void MainProgram::ExecuteGetShortestPathsBetweenAllVertices() {
  std::cout << "The shortest paths between all pairs of vertices: \n";
  if (matrix_.size() > 0) {
    matrix_ = controller_->GetShortestPathsBetweenAllVertices();
    PrintMatrix();
  }
}

void MainProgram::ExecuteGetLeastSpanningTree() {
  std::cout << "The minimal spanning tree in the graph: \n";
  if (matrix_.size() > 0) {
    matrix_ = controller_->GetLeastSpanningTree();
    PrintMatrix();
  }
}

void MainProgram::ExecuteSolveTravelingSalesmanProblem() {
  TsmResult tsm_result;

  tsm_result.distance = 0.0;
  if (matrix_.size() > 0) {
    tsm_result = controller_->SolveTravelingSalesmanProblem();
  }

  std::cout << "The solution of the traveling salesman problem: ";
  if (tsm_result.vertices.size() == 0) {
    std::cout
        << "error, it is impossible to solve the problem with a given graph\n";
  } else {
    std::cout << "\nsequence of traversing vertices: ";
    vector_ = tsm_result.vertices;
    PrintVector('-');
    std::cout << "route length: ";
    std::cout << tsm_result.distance << "\n";
  }
}

unsigned MainProgram::GetUnsignedFromStdin() {
  std::string num_str = "";
  std::cin >> num_str;

  return GetUnsignedFromString(num_str);
}

unsigned MainProgram::GetUnsignedFromString(const std::string &num_str) {
  std::istringstream num_str_iss(num_str);
  unsigned unsigned_num = 0;

  num_str_iss >> unsigned_num;

  return unsigned_num;
}

void MainProgram::PrintMatrix() {
  for (auto i = 0U; i < matrix_.size(); i++) {
    vector_ = matrix_[i];
    PrintVector(' ');
  }
}

void MainProgram::PrintVector(char delimiter) {
  for (auto j = 0U; j < vector_.size(); j++) {
    if (delimiter == ' ') {
      std::cout.width(4);
    }
    std::cout << vector_[j];
    if (j < vector_.size() - 1) {
      std::cout << delimiter;
    }
  }
  std::cout << "\n";
}
