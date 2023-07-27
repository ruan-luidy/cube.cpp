#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <Windows.h>

const int width = 100, height = 40;
std::vector<float> zBuffer(width * height, 0);
std::vector<char> buffer(width * height, ' ');

struct Point {
	float x, y, z;
};

void drawPixel(int x, int y, char ch) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		buffer[y * width + x] = ch;
	}
}

void calculateForSurface(float x, float y, char ch) {
	float ooz = 1.0f / y;
	int xp = static_cast<int>(width / 2 + x * 20 * ooz);
	int yp = static_cast<int>(height / 2 + 10 * ooz);
	int idx = xp + yp * width;
	if (idx >= 0 && idx < width * height && ooz > zBuffer[idx]) {
		zBuffer[idx] = ooz;
		drawPixel(xp, yp, ch);
	}
}

void rotatePoint(Point& point, float angle) {
	float s = std::sin(angle);
	float c = std::cos(angle);
	float xNew = point.x * c - point.y * s;
	float yNew = point.x * s + point.y * c;
	point.x = xNew;
	point.y = yNew;
}

int main() {
	std::cout << "zx1b[2J";
	std::cout << "x1b[?251";

	Point p1{ 0.0f, 3.0f, 10.0f };
	Point p2{ -3.0f, -3.0f, 10.0f };
	Point p3{ 3.0f, -3.0f, 10.0f };

	while (true) {
		std::fill(buffer.begin(), buffer.end(), ' ');
		std::fill(zBuffer.begin(), zBuffer.end(), 0);

		rotatePoint(p1, 0.05f);
		rotatePoint(p2, 0.05f);
		rotatePoint(p3, 0.05f);

		calculateForSurface(p1.x, p1.y, '/');
		calculateForSurface(p2.x, p2.y, '|');
		calculateForSurface(p3.x, p3.y, '\\');

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				std::cout << buffer[y * width + x];
			}
			std::cout << '\n';
		}

		Sleep(50);
	}

	std::cout << "x1b[?25h";
	return 0;
}