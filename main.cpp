#include <iostream>
#include <fstream>
#include <float.h>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "material.h"
#include "random"
#include "svpng.inc"
#include <iostream>

#define random(a, b) (rand()%(b-a+1)+a) //使用rand()的一个后果是，种子相同时每次的随机结果都相同
#define random1 (float((rand() % 100) / 100.f))

vec3 ray_color(const ray &r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    const int image_width = 600;
    const int image_height = 300;

    int ns = 100;

    // 调用svpng生成png格式图片
    unsigned char rgb[image_width * image_height * 3], *p = rgb;
    unsigned x, y;
    FILE *fp = fopen("pic.png", "wb");

    std::cout << "Pic: " << image_width << " * " << image_height << "\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = image_height - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto u = double(i) / image_width;
            auto v = double(j) / image_height;

            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 color = ray_color(r);

            // 将（0，1）映射到（0，255.99）
            int ir = static_cast<int>(255.99 * color[0]);
            int ig = static_cast<int>(255.99 * color[1]);
            int ib = static_cast<int>(255.99 * color[2]);
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
