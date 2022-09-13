//
// Created by yw_li on 2022/9/13.
//

#ifndef RAYTRACINGTOY_HITABLE_H
#define RAYTRACINGTOY_HITABLE_H

#include "ray.h"

struct hit_record {
	float t; // 射线参数t
	vec3 p; // 射线与物体的交点（碰撞点）
	vec3 normal; // 碰撞点处的法线向量
};

class hitable {
public:
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif //RAYTRACINGTOY_HITABLE_H
