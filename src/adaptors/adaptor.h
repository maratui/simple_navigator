#ifndef A2_SIMPLENAVIGATOR_ADAPTOR_H_
#define A2_SIMPLENAVIGATOR_ADAPTOR_H_

namespace s21 {
class Adaptor {
 public:
  virtual void Init() = 0;
  virtual void Push(unsigned value) = 0;
  virtual unsigned Pop() = 0;
  virtual bool Empty() const noexcept = 0;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_ADAPTOR_H_
