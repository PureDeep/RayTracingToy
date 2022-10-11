//
// Created by yw_li on 2022/9/13.
//

#ifndef RAYTRACINGTOY_SPHERE_H
#define RAYTRACINGTOY_SPHERE_H

#include "hitable.h"
#include "material.h"

class sphere : public hitable {
public:
	sphere() {}

	// 构造球心为cen，半径为r的球体
	sphere(vec3 cen, float r, material *mat) : center(cen), radius(r), mat_ptr(mat) {};

	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;

	vec3 center; // 球心坐标
	float radius; // 球体半径
	material *mat_ptr; // 球体材质
};

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record &rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		// 射线与球体相交时，找出参数t处于[tmin,tmax]范围内的交点
		// 两个交点都在范围内的话，返回参数t较小的那个（即先碰撞的点）
		// 将碰撞点信息存储rec中
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < tmax && temp > tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < tmax && temp > tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

#endif //RAYTRACINGTOY_SPHERE_H
