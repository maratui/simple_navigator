#ifndef A2_SIMPLENAVIGATOR_ANT_COLONY_ANT_COLONY_H_
#define A2_SIMPLENAVIGATOR_ANT_COLONY_ANT_COLONY_H_

#include <climits>
#include <cmath>
#include <random>
#include <vector>

namespace s21 {
class AntColony {
 public:
  AntColony() = delete;
  explicit AntColony(const std::vector<std::vector<double>> &distances,
                     unsigned iter_count);

  void Run();
  const std::vector<unsigned> &GetBestAntPaths() const noexcept;
  const double &GetMinDistance() const noexcept;

 private:
  void InitDistancesProbabilities();
  void CalculateTransitionProbabilities();
  void CalculateAntsPaths();
  bool IsAllVerticesInAntPath(unsigned ant) const noexcept;
  void FindRandomProbabilityVertex(unsigned ant, unsigned &vertex);
  void CalculateAntsDistances();
  void CalculatePheromones();
  void FindBestAnt();

  std::vector<std::vector<double>> distances_;
  std::vector<std::vector<double>> distances_probabilities_;
  std::vector<std::vector<double>> pheromones_;
  std::vector<std::vector<double>> pheromones_deltas_;
  std::vector<std::vector<double>> transition_probabilities_;
  std::vector<std::vector<unsigned>> ants_paths_;
  std::vector<double> ants_distances_;
  std::vector<unsigned> best_ant_paths_;
  std::vector<bool> is_used_;
  double pheromone_importance_{};
  double distance_significance_{};
  double pheromone_evaporation_{};
  double min_distance_{};
  unsigned vertices_count_{};
  unsigned ants_count_{};
  unsigned iter_count_{};
  unsigned best_ant_{};

  std::random_device rd_;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_ANT_COLONY_ANT_COLONY_H_
