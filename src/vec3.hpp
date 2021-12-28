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
  /**
   * @brief Construct a new null vec3 object
   *
   */
  explicit vec3() : x(0.0), y(0.0), z(0.0) {}

  /**
   * @brief Construct a new vec3 object specifying the values
   *
   * @param x The x value
   * @param y The y value
   * @param z The z value
   */
  explicit vec3(const double x, const double y, const double z)
      : x(x), y(y), z(z) {}

  /**
   * @brief Construct a new random vec3 object
   *
   * @param dis The random distribution
   * @param gen The Mersenne Twister generator
   */
  explicit vec3(uniform_real_distribution<double> &dis, mt19937 &gen)
      : x(dis(gen)), y(dis(gen)), z(dis(gen)) {}

  /**
   * @brief Set the x value
   *
   * @param x The new x value
   */
  void setX(double x) { x = x; }

  /**
   * @brief Set the y value
   *
   * @param y The new y value
   */
  void setY(double y) { y = y; }

  /**
   * @brief Set the new z value
   *
   * @param z The new z value
   */
  void setZ(double z) { z = z; }

  inline double getX() const { return x; }
  inline double getY() const { return y; }
  inline double getZ() const { return z; }

  /**
   * @brief Compute the square of the L2 norm of the vector
   *
   * @return double
   */
  inline double L2sNorm() const {
    return this->x * this->x + this->y * this->y + this->z * this->z;
  }

  /**
   * @brief Compute the L2 norm of the vector
   *
   * @return double
   */
  inline double L2Norm() const { return sqrt(this->L2sNorm()); }

  /**
   * @brief Normalize the vector, dividing it by its norm
   *
   * @return vec3
   */
  inline vec3 normalized() const {
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

  /**
   * @brief Overload of the operator << for vec3
   *
   * @param os
   * @return ostream&
   */
  friend inline ostream &operator<<(ostream &os, const vec3 &vec);
  friend inline vec3 operator*(const double &val, const vec3 &vec);
};

inline ostream &operator<<(ostream &os, const vec3 &vec) {
  os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";

  return os;
}

inline vec3 operator*(const double &val, const vec3 &vec) {
  return vec3(val * vec.x, val * vec.y, val * vec.z);
}