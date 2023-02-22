//
// Created by yw_li on 2022/9/13.
//

#ifndef RAYTRACINGTOY_HITTABLE_H
#define RAYTRACINGTOY_HITTABLE_H

#include "ray.h"
#include "rtweekend.h"

class material; //不完全声明

struct hit_record {
    double t; // 射线参数t
    vec3 p; // 射线与物体的交点（碰撞点）
    vec3 normal; // 碰撞点处的法线向量
    shared_ptr<material> mat_ptr; // 保存碰撞点处的材质
    bool front_face; // 用于判断入射面是正面还是反面

    /// 设置碰撞的入射面以及碰撞点的法线方向
    /// \param r 射线
    /// \param outward_normal 由物体中心点指向碰撞点的向量
    inline void set_face_normal(const ray &r, const vec3 &outward_normal) {
        // 如果入射方向与外侧法线点乘结果<0，则入射面是正面
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;

    virtual bool bounding_box(double t0, double t1, aabb &output_box) const = 0;
};

#endif //RAYTRACINGTOY_HITTABLE_H
