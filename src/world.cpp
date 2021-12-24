#include "world.hpp"

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