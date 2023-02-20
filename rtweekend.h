//
// Created by yw_li on 2023/2/19.
//

#ifndef RAYTRACINGTOY_RTWEEKEND_H
#define RAYTRACINGTOY_RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>

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

// Random
inline double random_double() {
    // 返回[0,1)之间的随机实数
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // 返回[min,max)之间的随机实数
    return min + (max - min) * random_double();
}

// Clamp
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Random vec3
inline static vec3 random_vec3() {
    return vec3(random_double(), random_double(), random_double());
}

inline static vec3 random_vec3(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

// Random point int unit sphere
vec3 random_in_unit_sphere() {
    while (true) {
        auto p = random_vec3(-1, 1);
        if (p.squared_lenght() >= 1) continue;
        return p;
    }
}

// 从单位圆盘射出光线
vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.squared_lenght() >= 1) continue;
        return p;
    }
}

// Random unit vector
vec3 random_unit_vector() {
    auto a = random_double(0, 2 * pi);  // 随机角度
    auto z = random_double(-1, 1);      // 随机z轴投影长度
    auto r = sqrt(1 - z * z);                  // xy平面投影长度
    return vec3(r * cos(a), r * sin(a), z); // 单位向量
}

// Random in hemisphere
vec3 random_in_hemisphere(const vec3 &normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // 半球法向与normal点乘大于0，处于同一半球
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

// Reflect vector
inline vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2 * dot(v, n) * n;
}

// 折射向量计算
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.squared_lenght()) * n;
    return r_out_parallel + r_out_perp;
}

// Christophe Schlick
double schlick(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif //RAYTRACINGTOY_RTWEEKEND_H
