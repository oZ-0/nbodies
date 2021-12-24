#pragma once
#include "vec3.hpp"
#include <vector>

using namespace std;

class World {
public:
  vector<vec3> position;
  vector<vec3> velocity;

public:
  explicit World(const int N=3)
      : position(vector<vec3>(N, vec3())), velocity(vector<vec3>(N, vec3())){};
  explicit World(const int N, vector<vec3> position)
      : position(position), velocity(vector<vec3>(N, vec3())){};
  explicit World(const int N, vector<vec3> position, vector<vec3> velocity)
      : position(position), velocity(velocity){};

  vec3 force(const int objId) const;
};