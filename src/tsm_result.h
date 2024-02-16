#ifndef A2_SIMPLENAVIGATOR_TSM_RESULT_H_
#define A2_SIMPLENAVIGATOR_TSM_RESULT_H_

#include <vector>

namespace s21 {
struct TsmResult {
  std::vector<unsigned> vertices;
  double distance;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_TSM_RESULT_H_
