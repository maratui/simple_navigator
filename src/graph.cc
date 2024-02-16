#include "graph.h"

using namespace s21;

void Graph::LoadGraphFromFile(const std::string &path) {
  std::ifstream in(path);

  adjacency_matrix_.clear();
  size_ = 0U;

  if (in.is_open()) {
    ReadSize(in);
    ReadAdjacencyMatrix(in);
  }
  in.close();
}

void Graph::ReadSize(std::ifstream &in) {
  std::string line = "";

  if (std::getline(in, line)) {
    std::istringstream line_iss(line);

    size_ = GetUnsignedFromLine(line_iss);
  }
}

void Graph::ReadAdjacencyMatrix(std::ifstream &in) {
  adjacency_matrix_.clear();
  for (auto i = 0U; (i < size_); i++) {
    std::string line = "";
    std::getline(in, line);
    std::istringstream line_iss(line);
    std::vector<unsigned> unsigned_vector;

    for (auto j = 0U; j < size_; j++) {
      unsigned_vector.push_back(GetUnsignedFromLine(line_iss));
    }
    adjacency_matrix_.push_back(unsigned_vector);
  }
}

unsigned Graph::GetUnsignedFromLine(std::istringstream &line_iss) {
  std::string num_str = "";
  unsigned unsigned_num = 0;

  while ((num_str == "") && (std::getline(line_iss, num_str, ' '))) {
  }
  std::istringstream num_str_iss(num_str);

  num_str_iss >> unsigned_num;

  return unsigned_num;
}

void Graph::ExportGraphToDot(const std::string &path) {
  std::ofstream out(path);

  if (out.is_open()) {
    out << "graph " << GetGraphName(path) << " {"
        << "\n";
    WriteAdjacencyMatrixToDot(out);
    out << "}\n";
  }
  out.close();
}

std::string Graph::GetGraphName(const std::string &path) noexcept {
  std::size_t pos = path.rfind("/");
  std::string graphname = path.substr(pos + 1);

  if ((pos = graphname.rfind(".")) != std::string::npos) {
    auto length = graphname.length();

    for (auto i = pos; i < length; i++) {
      graphname.pop_back();
    }
  }

  return graphname;
}

void Graph::WriteAdjacencyMatrixToDot(std::ofstream &out) {
  for (auto i = 1U; i <= size_; i++) {
    out << "  " << i << ";\n";
  }
  for (auto i = 0U; i < size_; i++) {
    for (auto j = i; j < size_; j++) {
      if (adjacency_matrix_[i][j] > 0) {
        out << "  " << i + 1U << " -- " << j + 1U << ";\n";
      }
    }
  }
}

unsigned Graph::GetSize() const noexcept { return size_; }

unsigned Graph::GetWeight(unsigned raw, unsigned col) const noexcept {
  return adjacency_matrix_[raw - 1U][col - 1U];
}

const std::vector<std::vector<unsigned>> &Graph::GetAdjacencyMatrix()
    const noexcept {
  return adjacency_matrix_;
}
