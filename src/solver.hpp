#pragma once
#include <string>
#include "world.hpp"

class GenericSolver {
protected:
  string name;

public:
  explicit GenericSolver() {}
  virtual void step(World &world_t) const = 0;
};

class EulerSolver : public GenericSolver {
protected:
  int N;
  double h;

public:
  explicit EulerSolver() : N(3), h(1.0) {}

  explicit EulerSolver(int N, double h) : N(N), h(h) {}

  void step(World &world_t) const;
};