#include "world.hpp"

int World::getNumObjects() const { return this->position.size(); }

vec3 World::force(const int objId) const {
  vec3 objPosition = this->position[objId];
  vec3 force_vec;
  for (int i = 0; i < this->position.size(); i++) {
    if (i != objId) {
      vec3 diff = this->position[i] - objPosition;
      force_vec += diff.normalized() / diff.L2sNorm();
    }
  }
  return force_vec;
}

double World::distance(const World &world) const {
  int size = this->position.size();
  double dist = 0;
  for (int i = 0; i < size; ++i) {
    dist += (this->position[i] - world.position[i]).L2Norm();
  }
  for (int i = 0; i < size; ++i) {
    dist += (this->velocity[i] - world.velocity[i]).L2Norm();
  }
  return dist;
}

World World::tilt(const int i, const double h) const {
  // check the dimension, check the object...
  int size = this->position.size();
  int object = i / (size*2);
  int dimension = i % (size*2);
  // cout << "size: " << size << "object " << object << "dimension: " << dimension
  //      << endl;
  vector<vec3> newPosition(this->position);
  vector<vec3> newVelocity(this->velocity);
  if (dimension <= 2) {
    newPosition[object][dimension] += h;
  } else {
    newVelocity[object][dimension - 3] += h;
  }
  return World(newPosition, newVelocity);
}