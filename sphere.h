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
    sphere(vec3 cen, float r, shared_ptr<material> mat) : center(cen), radius(r), mat_ptr(mat) {};

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    vec3 center; // 球心坐标
    float radius; // 球体半径
    shared_ptr<material> mat_ptr; // 球体材质
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
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

// Moving sphere
class moving_sphere : public hittable {
public:
    moving_sphere() {}

    moving_sphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, shared_ptr<material> m)
            : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) {};

    virtual bool hit(const ray &r, double tmin, double tmax, hit_record &rec) const;

    vec3 center(double time) const;

public:
    vec3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<material> mat_ptr;
};

vec3 moving_sphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray &r, double tmin, double tmax, hit_record &rec) const {
    vec3 oc = r.origin() - center(r.time());
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
        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}


#endif //RAYTRACINGTOY_SPHERE_H
