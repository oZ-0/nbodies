#pragma once
#include "world.hpp"
#include <string>

class GenericSolver {
protected:
  string name;

public:
  explicit GenericSolver() {}
  virtual void step(World &world_t) const = 0;
};

class EulerSolver : public GenericSolver {
protected:
  double h;

public:
  explicit EulerSolver() : h(1.0) {}

  explicit EulerSolver(double h) : h(h) {}

  void step(World &world_t) const;
};

class LeapFrogSolver : public GenericSolver {
protected:
  double h;

public:
  explicit LeapFrogSolver() : h(1.0) {}

  explicit LeapFrogSolver(double h) : h(h) {}

  void step(World &world_t) const;
};