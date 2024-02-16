#ifndef A2_SIMPLENAVIGATOR_STACK_H_
#define A2_SIMPLENAVIGATOR_STACK_H_

#include <vector>

#include "adaptor.h"

namespace s21 {
class Stack : public Adaptor {
 public:
  Stack() = default;

  void Init() override;
  void Push(unsigned value) override;
  unsigned Pop() override;
  bool Empty() const noexcept override;

  unsigned Top() const noexcept;

 private:
  std::vector<unsigned> vector_;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_STACK_H_
