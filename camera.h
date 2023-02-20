//
// Created by yw_li on 2022/9/15.
//

#ifndef RAYTRACINGTOY_CAMERA_H
#define RAYTRACINGTOY_CAMERA_H

#include "ray.h"

class camera {
public:
    camera(
            double vfov, // top to bottom, in degrees
            double aspect
    ) {
        origin = vec3(0.0, 0.0, 0.0);

        auto theta = degrees_to_radians(vfov);
        auto half_height = tan(theta / 2);
        auto half_width = aspect * half_height;

        lower_left_corner = vec3(-half_width, -half_height, -1.0);

        horizontal = vec3(2 * half_width, 0.0, 0.0);
        vertical = vec3(0.0, 2 * half_height, 0.0);
    }

    ray get_ray(double u, double v) {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif //RAYTRACINGTOY_CAMERA_H
