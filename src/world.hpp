#pragma once
#include "vec3.hpp"
#include <vector>
#define EPS 0.01

using namespace std;

class World {
public:
  /**
   * @brief The positions and velocities of the interacting objects
   *
   */
  vector<vec3> position, velocity;

public:
  explicit World(const int N = 3)
      : position(vector<vec3>(N, vec3())), velocity(vector<vec3>(N, vec3())) {}
  explicit World(const int N, const vector<vec3> &position)
      : position(position), velocity(vector<vec3>(N, vec3())) {}
  explicit World(const vector<vec3> &position, const vector<vec3> &velocity)
      : position(position), velocity(velocity) {}

  /**
   * @brief Construct a new random World object
   *
   * @param NObjects The number of interacting objects
   * @param dis The random distribution
   * @param gen The Mersenne Twister generator
   */
  explicit World(const int &NObjects, uniform_real_distribution<double> &dis,
                 mt19937 &gen) {
    for (int i = 0; i < NObjects; i++) {
      this->position.push_back(vec3(dis, gen));
      this->velocity.push_back(vec3(dis, gen));
    }
  }

  /**
   * @brief Construct a new World object by copy
   *
   * @param world The world to copy
   */
  explicit World(const World &world)
      : position(world.position), velocity(world.velocity) {}

  /**
   * @brief Compute the force vector applied to the chosen object
   *
   * @param objId The object on which to compute the force
   * @return vec3
   */
  vec3 force(const int objId) const;

  /**
   * @brief Construct a modified version of the current world
   * 
   * @param i The dimension of the value to be modified
   * @param h The modification coefficient
   * @return World 
   */
  World tilt(const int& i, const double& h) const;

  /**
   * @brief Compute the distance between two worlds.
   *
   * @param world The world to compare to
   * @return double
   */
  double distance(const World &world) const;

  /**
   * @brief Get the number of interacting objects
   * 
   * @return int
   */
  int getNumObjects() const;
  vector<vec3> getPosition() const { return position; }
  vector<vec3> getVelocity() const { return velocity; }

  void setPosition(const vector<vec3> pos) { this->position = pos; };
  void setVelocity(const vector<vec3> vel) { this->velocity = vel; };

  void operator+=(const vector<double> &grad) {
    int NObjects = this->position.size();
    for (int i = 0; i < NObjects * 3 * 2; i++) {
      int object = i / (NObjects * 2);
      int dimension = i % (NObjects * 2);
      if (dimension <= 2) {
        this->position[object][dimension] += grad[i];
      } else {
        this->velocity[object][dimension - 3] += grad[i];
      }
    }
  }

  void operator-=(const vector<double> &grad) {
    int NObjects = this->position.size();
    for (int i = 0; i < NObjects * 3 * 2; i++) {
      int object = i / (NObjects * 2);
      int dimension = i % (NObjects * 2);
      if (dimension <= 2) {
        this->position[object][dimension] -= grad[i];
      } else {
        this->velocity[object][dimension - 3] -= grad[i];
      }
    }
  }

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
  for (int i = 0; i < world.velocity.size(); i++) {
    os << "Velocities " << i << endl;
    os << "[" << world.velocity[i].getX() << ", " << world.velocity[i].getY()
       << ", " << world.velocity[i].getZ() << "]";
    if (i != world.velocity.size() - 1) {
      os << endl;
    }
  }
  return os;
}