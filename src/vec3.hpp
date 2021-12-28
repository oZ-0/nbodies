#pragma once
#include "exception.hpp"

#include <cmath>
#include <iostream>
#include <random>

using namespace std;

class vec3 {
protected:
  double x, y, z;

public:
  explicit vec3() : x(0.0), y(0.0), z(0.0) {}

  explicit vec3(const double x, const double y, const double z)
      : x(x), y(y), z(z) {}

  explicit vec3(uniform_real_distribution<double> &dis, mt19937 &gen)
      : x(dis(gen)), y(dis(gen)), z(dis(gen)) {}

  void setX(double x) { x = x; }
  void setY(double y) { y = y; }
  void setZ(double z) { z = z; }

  double getX() const { return x; }
  double getY() const { return y; }
  double getZ() const { return z; }

  inline double L2Norm() const {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
  }

  inline double L2sNorm() const {
    return this->x * this->x + this->y * this->y + this->z * this->z;
  }

  vec3 normalized() const {
    double norm = this->L2Norm();
    return (*this) / norm;
  }

  inline vec3 operator+(const vec3 &vec) const {
    return vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
  }

  inline vec3 operator-(const vec3 &vec) const {
    return vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
  }

  inline vec3 operator*(const double &val) const {
    return vec3(this->x * val, this->y * val, this->z * val);
  }

  inline double operator*(const vec3 &vec) const {
    return this->x * vec.x + this->y * vec.y + this->z * vec.z;
  }

  inline vec3 operator/(const double &val) const noexcept(false) {
    try {
      if (!val)
        throw val;
    } catch (double val) {
      cout << "Cannot divide by zero.\n";
      return *this;
    }
    return vec3(this->x / val, this->y / val, this->z / val);
  }

  inline vec3 &operator+=(const vec3 &vec) {
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
    return *this;
  }

  double operator[](int i) const {
    switch (i) {
    case 0:
      return this->x;
      break;
    case 1:
      return this->y;
      break;
    case 2:
      return this->z;
      break;
    default:
      break;
    }
  }
  double &operator[](int i) {
    switch (i) {
    case 0:
      return this->x;
      break;
    case 1:
      return this->y;
      break;
    case 2:
      return this->z;
      break;
    default:
      break;
    }
  }

  friend inline ostream &operator<<(ostream &os, const vec3 &vec);
  friend inline vec3 operator*(const double &val, const vec3 &vec);
};

/**
 * @brief Overload of the operator << for vec3
 *
 * @param os
 * @return ostream&
 */
inline ostream &operator<<(ostream &os, const vec3 &vec) {
  os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";

  return os;
}

inline vec3 operator*(const double &val, const vec3 &vec) {
  return vec3(val * vec.x, val * vec.y, val * vec.z);
}