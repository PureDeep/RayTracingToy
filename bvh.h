//
// Created by yw_li on 2023/2/22.
//

#ifndef RAYTRACINGTOY_BVH_H
#define RAYTRACINGTOY_BVH_H

#include "rtweekend.h"
#include "hittable.h"
#include "hittablelist.h"

class bvh_node : public hittable {
public:
    bvh_node();

    bvh_node(hittable_list &list, double time0, double time1)
            : bvh_node(list.objects, 0, list.objects.size(), time0, time1) {}

    bvh_node(std::vector<shared_ptr<hittable>> &objects, size_t start, size_t end, double time0, double time1);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;

    virtual bool bounding_box(double t0, double t1, aabb &output_box) const;

public:
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
    aabb box;
};

bool bvh_node::bounding_box(double t0, double t1, aabb &output_box) const {
    output_box = box;
    return true;
}

bool bvh_node::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    if (!box.hit(r, t_min, t_max))
        return false;

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

#endif //RAYTRACINGTOY_BVH_H
