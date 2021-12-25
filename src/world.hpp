#pragma once
#include "vec3.hpp"
#include <vector>
#define EPS 0.01

using namespace std;

class World {
public:
  vector<vec3> position;
  vector<vec3> velocity;

public:
  explicit World(const int N = 3)
      : position(vector<vec3>(N, vec3())), velocity(vector<vec3>(N, vec3())){};
  explicit World(const int N, vector<vec3> position)
      : position(position), velocity(vector<vec3>(N, vec3())){};
  explicit World(vector<vec3> position, vector<vec3> velocity)
      : position(position), velocity(velocity){};

  vec3 force(const int objId) const;

  /**
   * @brief Compute the distance between two worlds.
   * 
   * @param world The world to compare to
   * @return double 
   */
  double distance(const World& world) const;
  
  vector<vec3> getPosition() const { return position; }
  vector<vec3> getVelocity() const { return velocity; }

  void setPosition(const vector<vec3> pos) { this->position = pos; };
  void setVelocity(const vector<vec3> vel) { this->velocity = vel; };

  inline bool operator==(const World &world) const {
    int size = this->position.size();
    double sum = 0;
    for (int i = 0; i < size; ++i) {
      sum += (this->position[i] - world.position[i]).L2Norm();
    }
    for (int i = 0; i < size; ++i) {
      sum += (this->velocity[i] - world.velocity[i]).L2Norm();
    }
    return sum < EPS;
  }

  /**
   * @brief Overload of the operator << for the world
   *
   * @param os
   * @return ostream&
   */
  friend inline ostream &operator<<(ostream &os, const World &world);
};

inline ostream &operator<<(ostream &os, const World &world) {
  for (int i = 0; i < world.position.size(); i++) {
    os << "Positions " << i << endl;
    os << "[" << world.position[i].getX() << ", " << world.position[i].getY()
       << ", " << world.position[i].getZ() << "]" << endl;
  }
  for (int i = 0; i < world.position.size(); i++) {
    os << "Velocities " << i << endl;
    os << "[" << world.velocity[i].getX() << ", " << world.velocity[i].getY()
       << ", " << world.velocity[i].getZ() << "]";
    if (i != world.position.size() - 1) {
      os << endl;
    }
  }
  return os;
}