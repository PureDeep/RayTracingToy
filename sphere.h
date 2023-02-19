//
// Created by yw_li on 2022/9/13.
//

#ifndef RAYTRACINGTOY_SPHERE_H
#define RAYTRACINGTOY_SPHERE_H

#include "hittable.h"
#include "material.h"

class sphere : public hittable {
public:
    sphere() {}

    // 构造球心为cen，半径为r的球体
    sphere(vec3 cen, float r/*, material *mat*/) : center(cen), radius(r)/*, mat_ptr(mat)*/ {};

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    vec3 center; // 球心坐标
    float radius; // 球体半径
    //material *mat_ptr; // 球体材质
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().squared_lenght();
    auto half_b = dot(oc, r.direction());
    float c = oc.squared_lenght() - radius * radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        // 射线与球体相交时，找出参数t处于[t_min,t_max]范围内的交点
        // 两个交点都在范围内的话，返回参数t较小的那个（即先碰撞的点）
        // 将碰撞点信息存储rec中
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            //rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            //rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif //RAYTRACINGTOY_SPHERE_H
