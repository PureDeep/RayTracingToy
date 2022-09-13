//
// Created by yw_li on 2022/9/13.
//

#ifndef RAYTRACINGTOY_HITABLE_H
#define RAYTRACINGTOY_HITABLE_H

#include "ray.h"

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
};

class hitable {
public:
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif //RAYTRACINGTOY_HITABLE_H
