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

///
/// \param r 射线
/// \param world 可碰撞物体
/// \param depth 反射深度
/// \return 射线交点处的颜色，发生碰撞返回碰撞点法线，未发生碰撞返回背景色
vec3 color(const ray &r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.0001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;

		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		} else {
			return vec3(0, 0, 0);
		}
	} else {
		// 如果射线没有与物体发生碰撞，则返回背景的颜色
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}


int main() {
	int nx = 600;
	int ny = 300;

	int ns = 100;

	// 以写模式打开文件
//	std::ofstream outfile;
//	outfile.open("color.ppm");

	// PPM格式，P3表示颜色以ASCII表示，200行，100列，最大颜色数量255
	//outfile << "P3\n" << nx << " " << ny << "\n255\n";

	camera cam;

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3))); // 球1
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.8))); // 球2
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2))); // 球3金属球
	//list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1)); // 球4玻璃球
	//list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2))); // 球4金属球
	hitable *world = new hitable_list(list, 3);

	// 调用svpng生成png格式图片
	unsigned char rgb[nx * ny * 3], *p = rgb;
	unsigned x, y;
	FILE *fp = fopen("color.png", "wb");
//	for (y = 0; y < ny; y++)
//		for (x = 0; x < nx; x++) {
//			*p++ = (unsigned char)x;    /* R */
//			*p++ = (unsigned char)y;    /* G */
//			*p++ = 128;                 /* B */
//		}
//	svpng(fp, nx, ny, rgb, 0);
//	fclose(fp);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);

			// 随机生成ns个采样点，并将颜色叠加
			for (int s = 0; s < ns; s++) {
				//srand((unsigned) time(NULL));
				float u = float((i + random(0, 100) / 100) / float(nx));
				float v = float((j + random(0, 100) / 100) / float(ny));

				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}

			col /= float(ns);
			// 进行gamma补偿
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			// 将（0，1）映射到（0，255.99）
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			//outfile << ir << " " << ig << " " << ib << "\n";

			*p++ = (unsigned char)ir;    /* R */
			*p++ = (unsigned char)ig;    /* G */
			*p++ = (unsigned char)ib;    /* B */
		}
	}

	//outfile.close();

	svpng(fp, nx, ny, rgb, 0);
	fclose(fp);

	return 0;
}
