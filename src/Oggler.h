#ifndef _OGGLER_H_
  #define _OGGLER_H_

#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Orientable.h"

/// \brief OpenGL Camera
///
/// A camera class which can modify OpenGL stack to mimic camera movement.
/// \n Attaches to an Orientable

// Oggler OpenGL Camera
// Attached to an Orientable, attempts to emulate interface
class Oggler {
  public:
    /// \brief Orientable to which the camera is attached
    Orientable* dolly;
    /// \brief Whether the current dolly is one used for the sole purpose of carrying the camera
    bool own_dolly;

    /// \brief Field of view
    float fov;
    /// \brief Aspect ratio to display to
    float aspect;
    /// \brief Near clipping plane
    float near;
    /// \brief Far clipping plane
    float far;

  public:
    Oggler();
    Oggler(Orientable*);

    /// \brief Attach camera to orientable
    void attach(Orientable*);

    /// \brief Assign sight parameters
    void settings(float _fov, float _aspect, float _near, float _far);

    /// \brief Applies MODELVIEW transformation
    void view_model();
    /// \brief Applies PERSPECTIVE transformation
    void view_perspective();
};

#endif
