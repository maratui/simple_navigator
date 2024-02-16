#include "stack.h"

using namespace s21;

void Stack::Init() {
  while (vector_.empty() == false) {
    vector_.pop_back();
  }
}

void Stack::Push(unsigned value) { vector_.push_back(value); }

unsigned Stack::Pop() {
  unsigned value = vector_.back();

  vector_.pop_back();

  return value;
}

bool Stack::Empty() const noexcept { return vector_.empty(); }

unsigned Stack::Top() const noexcept { return vector_.back(); }
