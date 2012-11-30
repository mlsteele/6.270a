#ifndef _ORIENTABLE_H_
  #define _ORIENTABLE_H_

#include "V3D.h"

/// \brief Object in space with orientation.
/// 
/// \n Holds position (vector), and orientation (3 vectors).
/// \n Orientation is represented by right, up, and forward directions.
/// \n Default orientation uses a negative z axis as forward for OpenGL compliance.

class Orientable {
  public:
    /// position Vector
    V3D<float> pos;
    /// Rotation right component
    V3D<float> rt;
    /// Rotation up component
    V3D<float> up;
    /// Rotation forward component
    V3D<float> fd;
  
  public:
    Orientable();
    
    // Translation
    
    /// \brief Translates along global space
    void translate_global(V3D<float> _offset);
    inline void translate_global (float _x, float _y, float _z) {translate_global(V3D<float>(_x, _y, _z));};
    
    /// \brief Translates along local space
    void translate_local(V3D<float> _offset);
    inline void translate_local (float _x, float _y, float _z) {translate_local(V3D<float>(_x, _y, _z));};
    
    // Rotation
    
    /// \brief Rotate around right
    void pitch(float);
    /// \brief Rotate around up
    void yaw(float);
    /// \brief Rotate around forward
    void roll(float);
    
    /// \brief Return to default orientation and position
    void zero();
    
    /// \brief Unitize directions if they have decayed
    void calibrate();
    
    /// \brief Convert from local to global space
    inline V3D<float> LTG(V3D<float> L) const {
      V3D<float> G = (rt * L.x) + (up * L.y) + (fd * L.z);
      G += pos;
      return G;
    }
    /// \brief Convert from global to local space
    inline V3D<float> GTL(V3D<float> G) const {
      V3D<float> L(G);
      L -= pos;
      L = V3D<float>(rt.dot(L), up.dot(L), fd.dot(L));
      return L;
    }
    
    /// \brief Convert from local orientation to global orientation
    inline V3D<float> OLTG(V3D<float> L) const {
      V3D<float> G = (rt * L.x) + (up * L.y) + (fd * L.z);
      return G;
    }
    /// \brief Convert from global orientation to local orientation
    inline V3D<float> OGTL(V3D<float> G) const {
      V3D<float> L(G);
      L = V3D<float>(rt.dot(L), up.dot(L), fd.dot(L));
      return L;
    }
};

#endif
