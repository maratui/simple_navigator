#ifndef A2_SIMPLENAVIGATOR_QUEUE_H_
#define A2_SIMPLENAVIGATOR_QUEUE_H_

#include <vector>

#include "adaptor.h"

namespace s21 {
class Queue : public Adaptor {
 public:
  Queue() = default;

  void Init() override;
  void Push(unsigned value) override;
  unsigned Pop() override;
  bool Empty() const noexcept override;

  unsigned Front() const noexcept;
  unsigned Back() const noexcept;

 private:
  std::vector<unsigned> vector_;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_QUEUE_H_
