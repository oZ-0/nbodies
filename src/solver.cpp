#include "solver.hpp"

World EulerSolver::step(const World &world_t) const {
    vector<vec3> position_tp1(this->N, vec3());
    vector<vec3> velocity_tp1(this->N, vec3());

    for (int ObjId = 0; ObjId < this->N; ObjId++) {
      velocity_tp1[ObjId] =
          world_t.velocity[ObjId] + this->h * world_t.force(ObjId);
      position_tp1[ObjId] =
          world_t.position[ObjId] + this->h * world_t.velocity[ObjId];
    }
    return World(position_tp1.size(), position_tp1, velocity_tp1);
  }