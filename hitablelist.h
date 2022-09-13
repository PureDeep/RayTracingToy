//
// Created by yw_li on 2022/9/13.
//

#ifndef RAYTRACINGTOY_HITABLELIST_H
#define RAYTRACINGTOY_HITABLELIST_H

#include "hitable.h"

class hitable_list : public hitable {
public:
	hitable_list() {}

	hitable_list(hitable **l, int n) {
		list = l;
		list_size = n;
	}

	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;

	hitable **list; // 元素类型为hitable的数组
	int list_size; // hitable list元素个数
};

bool hitable_list::hit(const ray &r, float tmin, float tmax, hit_record &rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	double closet_so_far = tmax;
	// 对hitable list中的所有元素进行hit检测，并将最近的hit信息存入rec中
	for (int i = 0; i < list_size; i++) {
		// 每次只对[tmin, closet_so_far]范围内的检测hit，即
		if (list[i]->hit(r, tmin, closet_so_far, temp_rec)) {
			hit_anything = true;
			closet_so_far = temp_rec.t; // 更新closet_so_far信息，closet_so_far只会越来越小
			rec = temp_rec;
		}
	}
	return hit_anything;
}

#endif //RAYTRACINGTOY_HITABLELIST_H
