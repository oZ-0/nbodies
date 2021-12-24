#pragma once
#include <vector>
#include "vec3.hpp"
#include "globals.hpp"

using namespace std;

class World {
public:
  vector<vec3> position;
  vector<vec3> velocity;

public:
  explicit World()
      : position(vector<vec3>(N, vec3())), velocity(vector<vec3>(N, vec3())){};
  explicit World(vector<vec3> position,
                 vector<vec3> velocity = vector<vec3>(N, vec3()))
      : position(position), velocity(velocity){};

  vec3 force(const int objId) const;
};