#include <iostream>
#include <fstream>

int main() {
	int nx = 200;
	int ny = 100;

	// 以写模式打开文件
	std::ofstream outfile;
	outfile.open("color.ppm");

	// PPM格式，P3表示颜色以ASCII表示，200行，100列，最大颜色数量255
	outfile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			// 将（0，1）扩张到（0，255.99）
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			outfile << ir << " " << ig << " " << ib << "\n";
		}
	}

	outfile.close();

	return 0;
}
