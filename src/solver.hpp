#pragma once
#include <string>
#include "world.hpp"

class GenericSolver {
protected:
  string name;

public:
  explicit GenericSolver() {}
  virtual World step(const World &world_t) const = 0;
};

class EulerSolver : public GenericSolver {
protected:
  double h;

public:
  explicit EulerSolver() : h(1.0) {}
  explicit EulerSolver(double h) : h(h) {}
  World step(const World &world_t) const {
    vector<vec3> position_tp1(N, vec3());
    vector<vec3> velocity_tp1(N, vec3());

    for (int ObjId = 0; ObjId < N; ObjId++) {
      velocity_tp1[ObjId] =
          world_t.velocity[ObjId] + this->h * world_t.force(ObjId);
      position_tp1[ObjId] =
          world_t.position[ObjId] + this->h * world_t.velocity[ObjId];
    }
    return World(position_tp1, velocity_tp1);
  }
};