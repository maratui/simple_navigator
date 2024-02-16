#include "queue.h"

using namespace s21;

void Queue::Init() {
  while (vector_.empty() == false) {
    vector_.pop_back();
  }
}

void Queue::Push(unsigned value) { vector_.push_back(value); }

unsigned Queue::Pop() {
  unsigned value = vector_.front();

  vector_.erase(vector_.begin());

  return value;
}

bool Queue::Empty() const noexcept { return vector_.empty(); }

unsigned Queue::Front() const noexcept { return vector_.front(); }

unsigned Queue::Back() const noexcept { return vector_.back(); }
