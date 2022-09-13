#include <iostream>
#include <fstream>
#include <float.h>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"

///
/// \param r 射线
/// \param world 可碰撞物体
/// \return 射线交点处的颜色，发生碰撞返回碰撞点法线，未发生碰撞返回背景色
vec3 color(const ray &r, hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec)) {
		// 如果射线与物体发生碰撞，则将碰撞点法线向量从[-1,1]映射到[0,1]
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	} else {
		// 如果射线没有与物体发生碰撞，则返回背景的颜色
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main() {
	int nx = 200;
	int ny = 100;

	// 以写模式打开文件
	std::ofstream outfile;
	outfile.open("color.ppm");

	// PPM格式，P3表示颜色以ASCII表示，200行，100列，最大颜色数量255
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0); // 定义左下角
	vec3 horizontal(4.0, 0.0, 0.0); // x轴向右，最大为4
	vec3 vertical(0.0, 2.0, 0.0); // y轴向上，最高为2
	vec3 origin(0.0, 0.0, 0.0); // 摄像机在坐标原点

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 p = r.point_at_parameter(2.0);
			vec3 col = color(r, world);

			// 将（0，1）映射到（0，255.99）
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			outfile << ir << " " << ig << " " << ib << "\n";
		}
	}

	outfile.close();

	return 0;
}
