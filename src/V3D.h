// 3 dimensional vector
// Comprised of Ts
/// \brief 3 Dimensional Vector
///
/// Holder for 3 Ts as well as common vector operations

#ifndef _V3D_H_
#define _V3D_H_

#include <iostream>
#include <cmath>

template <class T>
class V3D {
public:
  /// \brief x-axis component
  T x;
  /// \brief y-axis component
  T y;
  /// \brief z-axis component
  T z;


// Public Operations
public:

  /// \brief Default zero constructor
  inline V3D() {
    x = 0;
    y = 0;
    z = 0;
  };

  /// \brief Initial values constructor
  inline V3D(T _x, T _y, T _z) {
    x = _x;
    y = _y;
    z = _z;
  };

  /// \brief Access by indices 0, 1, 2
  // This may be slower than dot access.
  inline T operator[] (int i) {
    switch (i) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        throw "Error: Index out of bounds";
    }
  };

  /// \brief Zeroes out components
  inline void zero() {
    x = 0;
    y = 0;
    z = 0;
  };

  inline bool operator==(const V3D& _v) {
    return x == _v.x && y == _v.y && z == _v.z; 
  }

  /// \brief Set vector value
  inline void set(T _x, T _y, T _z) {set(V3D(_x, _y, _z));};
  /// \brief Set vector value
  inline void set(V3D _in) {
    x = _in.x;
    y = _in.y;
    z = _in.z;
  };

  /// \brief Vector addition (set)
  inline V3D& operator+= (const V3D& _vec) {
    x += _vec.x;
    y += _vec.y;
    z += _vec.z;
    return *this;
  };

  /// \brief Vector subtraction (set)
  inline V3D& operator-= (const V3D& _vec) {
    x -= _vec.x;
    y -= _vec.y;
    z -= _vec.z;
    return *this;
  };

  /// \brief Scalar multiplication (set)
  inline V3D& operator*= (const T &s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  };

  /// \brief Scalar division (set)
  inline V3D& operator/= (const T &s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  };

  /// \brief Negation
  inline const V3D operator- () const {
    return V3D(-x, -y, -z);
  };

  /// \brief Vector Addition (no set)
  inline const V3D operator+ (const V3D& _v) const {
    return V3D(*this) += _v;
  };

  /// \brief Vector Subtraction (no set)
  inline const V3D operator- (const V3D& _v) const {
    return V3D(*this) -= _v;
  };

  /// \brief Scalar Multiplication (no set)
  inline const V3D operator* (const T &s) const {
    return V3D(*this) *= s;
  };

  /// \brief Scalar Divison (no set)
  inline const V3D operator/ (const T &s) const {
    return V3D(*this) /= s;
  };

  /// \brief Spins around the given UNIT vector
  inline void spin_unit(T _theta, V3D _axis) {
    T u = _axis.x;
    T v = _axis.y;
    T w = _axis.z;

    // http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/ArbitraryAxisRotation.html
    T nx = u*(u*x + v*y + w*z)*(1 - cos(_theta)) + x*cos(_theta) + (- w*y + v*z)*sin(_theta);
    T ny = v*(u*x + v*y + w*z)*(1 - cos(_theta)) + y*cos(_theta) + (w*x - u*z)*sin(_theta);
    T nz = w*(u*x + v*y + w*z)*(1 - cos(_theta)) + z*cos(_theta) + (- v*x + u*y)*sin(_theta);

    set(nx, ny, nz);
  };

  /// \brief Compute the length of a vector
  inline T len() const {
    return sqrt( x*x + y*y + z*z );
  };

  /// \brief Compute the length squared of a vector
  inline T lenSq() const {
    return x*x + y*y + z*z;
  };

  /// \brief Normalize vector into unit (set)
  inline void normalize() {
    T len = this->len();
    x /= len;
    y /= len;
    z /= len;
  };

  /// \brief Return normalized vector
  inline const V3D normalized() const {
    V3D result = V3D(x, y, z);
    result.normalize();
    return result;
  };

  /// \brief Dot product of two vectors
  inline T dot(const V3D& _v) const {
    return (x*_v.x + y*_v.y + z*_v.z);
  };

  inline void print(std::string ID) const {
    std::cout << ID << " -> V3D( " << x << ", " << y << ", " << z << " )\n";
  }

  inline void print() const {
    std::cout << "V3D( " << x << ", " << y << ", " << z << " )\n";
  }
};

#endif
