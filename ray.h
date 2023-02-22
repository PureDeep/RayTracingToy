//
// Created by yw_li on 2022/9/12.
//

#ifndef RAYTRACINGTOY_RAY_H
#define RAYTRACINGTOY_RAY_H

#include "vec3.h"

class ray {
public:
    ray() {}

    /// 声明一条射线
    /// \param origin 射线起点
    /// \param direction 射线终点
    ray(const vec3 &origin, const vec3 &direction, double time = 0.0)
            : orig(origin), dir(direction), tm(time) {
    }

    /// 返回射线起点
    /// \return 射线起点
    vec3 origin() const { return orig; }

    /// 返回射线的指向
    /// \return 射线的指向
    vec3 direction() const { return dir; }

    double time() const { return tm; }

    /// 返回射线上某一点
    /// \param t
    /// \return
    vec3 at(double t) const { return orig + dir * t; }

    vec3 orig;
    vec3 dir;
    double tm;
};

#endif //RAYTRACINGTOY_RAY_H
