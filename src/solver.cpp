#include "solver.hpp"

using namespace std;

void EulerSolver::step(World &world_t) const {
  int size = world_t.position.size();
  vector<vec3> position_tp1(size, vec3());
  vector<vec3> velocity_tp1(size, vec3());

  for (int ObjId = 0; ObjId < size; ObjId++) {
    velocity_tp1[ObjId] =
        world_t.velocity[ObjId] + this->h * world_t.force(ObjId);
    position_tp1[ObjId] =
        world_t.position[ObjId] + this->h * world_t.velocity[ObjId];
  }
  world_t = World(position_tp1, velocity_tp1);
}

void LeapFrogSolver::step(World &world_t) const {
  int size = world_t.position.size();
  vector<vec3> position_tp1(size, vec3());
  vector<vec3> velocity_tp1(size, vec3());

  for (int ObjId = 0; ObjId < size; ObjId++) {
    position_tp1[ObjId] =
        world_t.position[ObjId] + this->h * world_t.velocity[ObjId];
  }
  world_t.setPosition(position_tp1);
  for (int ObjId = 0; ObjId < size; ObjId++) {
    velocity_tp1[ObjId] =
        world_t.velocity[ObjId] + this->h * world_t.force(ObjId);
  }
  world_t.setVelocity(velocity_tp1);
}