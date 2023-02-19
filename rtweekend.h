//
// Created by yw_li on 2023/2/19.
//

#ifndef RAYTRACINGTOY_RTWEEKEND_H
#define RAYTRACINGTOY_RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings
using std::shared_ptr;
using std::make_shared;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }

inline double ffmax(double a, double b) { return a >= b ? a : b; }

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif //RAYTRACINGTOY_RTWEEKEND_H
