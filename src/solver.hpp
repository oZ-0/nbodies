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

class Yoshida4Solver : public GenericSolver {
protected:
  double h;
  double w0 = - pow(2, 1.5)/(2-pow(2, 1.5));
  double w1 = 1/(2-pow(2, 1.5));
  double c1 = w1/2;
  double c2 = (w0+w1)/2;

public:
  explicit Yoshida4Solver() : h(1.0) {}

  explicit Yoshida4Solver(double h) : h(h) {}

  void step(World &world_t) const;
};