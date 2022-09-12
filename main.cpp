#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

/// color(ray)函数根据Y坐标的上/下限线性地混合白色和蓝色。
/// \param r 射线
/// \return 返回射线所指向的点的颜色
vec3 color(const ray &r) {
	vec3 unit_direction = unit_vector(r.direction()); // 射线的单位方向向量
	float t = 0.5 * (unit_direction.y() + 1.0);
	// 返回混合后的值
	// vec3(1.0, 1.0, 1.0)是白色，vec3(0.5, 0.7, 1.0f)是蓝色
	return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
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

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);

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
