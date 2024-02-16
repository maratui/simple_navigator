#include "ant_colony.h"

using namespace s21;

AntColony::AntColony(const std::vector<std::vector<double>> &distances,
                     unsigned iter_count)
    : distances_(distances), iter_count_(iter_count) {
  InitDistancesProbabilities();
  pheromones_.assign(distances_.size(),
                     std::vector<double>(distances_.size(), 1.0));
  transition_probabilities_.assign(distances_.size(),
                                   std::vector<double>(distances_.size(), 0.0));
  vertices_count_ = distances_.size();
  ants_count_ = vertices_count_;
  pheromone_importance_ = 2.0;
  distance_significance_ = 2.0;
  pheromone_evaporation_ = 0.1;
}

void AntColony::InitDistancesProbabilities() {
  distances_probabilities_ = distances_;
  for (auto i = 0U; i < distances_probabilities_.size(); i++) {
    for (auto j = 0U; j < distances_probabilities_[i].size(); j++) {
      if (distances_probabilities_[i][j] > 0.0) {
        distances_probabilities_[i][j] = 1.0 / distances_probabilities_[i][j];
      } else {
        distances_probabilities_[i][j] = 0.0;
      }
    }
  }
}

void AntColony::Run() {
  if (distances_.size() > 0) {
    for (auto iter = 0U; iter < iter_count_; iter++) {
      CalculateTransitionProbabilities();
      CalculateAntsPaths();
      CalculateAntsDistances();
      CalculatePheromones();
    }
    FindBestAnt();
  }
}

void AntColony::CalculateTransitionProbabilities() {
  for (auto i = 0U; i < transition_probabilities_.size(); i++) {
    for (auto j = 0U; j < transition_probabilities_[i].size(); j++) {
      transition_probabilities_[i][j] =
          pow(pheromones_[i][j], pheromone_importance_) *
          pow(distances_probabilities_[i][j], distance_significance_);
    }
  }
}

void AntColony::CalculateAntsPaths() {
  ants_paths_.assign(ants_count_, std::vector<unsigned>());
  for (auto ant = 0U; ant < ants_count_; ant++) {
    bool is_calculated = false;

    ants_paths_[ant].push_back(ant);
    is_used_.assign(vertices_count_, false);
    is_used_[ant] = true;
    for (auto i = 0U; (i < 10U) && (is_calculated == false); i++) {
      for (auto j = 0U; (j < vertices_count_) && (is_calculated == false);
           j++) {
        unsigned vertex = UINT_MAX;

        FindRandomProbabilityVertex(ant, vertex);
        if (vertex != UINT_MAX) {
          ants_paths_[ant].push_back(vertex);
          is_used_[vertex] = true;
        }
        is_calculated = ((ants_paths_[ant].back() == ant) &&
                         (IsAllVerticesInAntPath(ant) == true));
      }
      is_used_.assign(vertices_count_, false);
    }
  }
}

bool AntColony::IsAllVerticesInAntPath(unsigned ant) const noexcept {
  bool is_contains = true;

  for (unsigned j = 0U; (j < vertices_count_) && (is_contains == true); j++) {
    is_contains = false;
    for (unsigned vertex : ants_paths_[ant]) {
      if (j == vertex) {
        is_contains = true;
        break;
      }
    }
  }

  return is_contains;
}

void AntColony::FindRandomProbabilityVertex(unsigned ant, unsigned &vertex) {
  unsigned i_vertex = ants_paths_[ant].back();
  double probabilities_sum = 0.0;

  for (auto j_vertex = 0U; j_vertex < vertices_count_; j_vertex++) {
    if (is_used_[j_vertex] == false) {
      probabilities_sum += transition_probabilities_[i_vertex][j_vertex];
    }
  }

  if (probabilities_sum > 0.0) {
    std::uniform_real_distribution<> dis(0.0, probabilities_sum);
    std::mt19937_64 gen(rd_());
    double random_value = dis(gen);

    for (auto j_vertex = 0U;
         (j_vertex < vertices_count_) && (random_value >= 0.0); j_vertex++) {
      if (is_used_[j_vertex] == false) {
        random_value -= transition_probabilities_[i_vertex][j_vertex];
        if (random_value < 0.0) {
          vertex = j_vertex;
        }
      }
    }
  }
}

void AntColony::CalculateAntsDistances() {
  ants_distances_.assign(ants_count_, 0.0);
  for (auto ant = 0U; ant < ants_count_; ant++) {
    unsigned i_vertex = ants_paths_[ant][0U];

    ants_distances_[ant] = 0.0;
    for (auto j = 1U; j < ants_paths_[ant].size(); j++) {
      unsigned j_vertex = ants_paths_[ant][j];

      ants_distances_[ant] += distances_[i_vertex][j_vertex];
      i_vertex = j_vertex;
    }
  }
}

void AntColony::CalculatePheromones() {
  pheromones_deltas_.assign(pheromones_.size(),
                            std::vector<double>(pheromones_.size(), 0.0));
  for (auto ant = 0U; ant < ants_count_; ant++) {
    unsigned i_vertex = ants_paths_[ant][0U];

    if (ants_distances_[ant] > 0.0) {
      for (auto j = 1U; j < ants_paths_[ant].size(); j++) {
        unsigned j_vertex = ants_paths_[ant][j];

        pheromones_deltas_[i_vertex][j_vertex] += 1.0 / ants_distances_[ant];
        i_vertex = j_vertex;
      }
    }
  }

  for (auto i = 0U; i < pheromones_.size(); i++) {
    for (auto j = 0U; j < pheromones_[i].size(); j++) {
      pheromones_[i][j] = (1.0 - pheromone_evaporation_) * pheromones_[i][j] +
                          pheromones_deltas_[i][j];
    }
  }
}

void AntColony::FindBestAnt() {
  best_ant_paths_.clear();
  best_ant_ = UINT_MAX;
  min_distance_ = 1.0e10;
  for (auto ant = 0U; ant < ants_count_; ant++) {
    if ((min_distance_ > ants_distances_[ant]) &&
        (IsAllVerticesInAntPath(ant) == true)) {
      min_distance_ = ants_distances_[ant];
      best_ant_ = ant;
    }
  }
  if ((best_ant_ < ants_count_) && (ants_paths_.size() > 0)) {
    best_ant_paths_ = ants_paths_[best_ant_];
  }
}

const std::vector<unsigned> &AntColony::GetBestAntPaths() const noexcept {
  return best_ant_paths_;
}
const double &AntColony::GetMinDistance() const noexcept {
  return min_distance_;
}
