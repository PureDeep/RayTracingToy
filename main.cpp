#include <iostream>
#include <fstream>
#include <float.h>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittablelist.h"
#include "camera.h"
#include "material.h"
#include "random"
#include "svpng.inc"
#include "rtweekend.h"
#include <iostream>

//#define random(a, b) (rand()%(b-a+1)+a) //使用rand()的一个后果是，种子相同时每次的随机结果都相同
//#define random1 (float((rand() % 100) / 100.f))

// 球体表面法相
double hit_sphere(const vec3 &center, double radius, const ray &r) {
    vec3 oc = r.origin() - center;

    // 求根公式 b = 2 * half_b
    auto a = r.direction().squared_lenght();
    auto half_b = dot(oc, r.direction());
    auto c = oc.squared_lenght() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

vec3 ray_color(const ray &r, const hittable &world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) {
        return vec3(0, 0, 0);
    }

    // 如果相交
    if (world.hit(r, 0, infinity, rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
    }

    // 如果不相交
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    const int image_width = 600;
    const int image_height = 300;
    const int samples_per_pixel = 100;
    const int max_depth = 100;

    // 调用svpng生成png格式图片
    unsigned char rgb[image_width * image_height * 3], *p = rgb;
    unsigned x, y;
    FILE *fp = fopen("pic.png", "wb");

    std::cout << "Pic: " << image_width << " * " << image_height << "\n";

    // 场景
    hittable_list world;
    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));

    // 相机
    camera cam;

    for (int j = image_height - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            vec3 color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world, max_depth);
            }

            auto scale = 1.0 / samples_per_pixel;

            // 将（0，1）映射到（0，255.99）
            int ir = static_cast<int>(255.99 * color[0]) * scale;
            int ig = static_cast<int>(255.99 * color[1]) * scale;
            int ib = static_cast<int>(255.99 * color[2]) * scale;
            //outfile << ir << " " << ig << " " << ib << "\n";

            *p++ = (unsigned char) ir;    /* R */
            *p++ = (unsigned char) ig;    /* G */
            *p++ = (unsigned char) ib;    /* dir */
        }
    }

    svpng(fp, image_width, image_height, rgb, 0);
    fclose(fp);

    std::cerr << "\nDone.\n";

    return 0;
}
