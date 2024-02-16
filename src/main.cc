#include "main_program.h"

int main() {
  s21::Facade facade;
  s21::Controller controller(&facade);
  s21::MainProgram main_program(&controller);

  return main_program.Execute();
}
