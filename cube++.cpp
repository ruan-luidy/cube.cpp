#include <iostream>
#include <cmath>
#include <cstring>
#include <thread>
#include <chrono>

using namespace std;

float A, B, C;

float cubeWidth = 20;
int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = '.';
int distanceFromCam = 100;
float horizontalOffset;
float K1 = 40;

float incrementSpeed = 0.6;

float x, y, z;
float ooz;
int xp, yp;
int idx;

float calculateX(int i, int j, int k) {
	return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
		j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k) {
	return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
		j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
		i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k) {
	return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
	x = calculateX(cubeX, cubeY, cubeZ);
	y = calculateY(cubeX, cubeY, cubeZ);
	z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

	ooz = 1 / z;

	xp = static_cast<int>(width / 2 + horizontalOffset + K1 * ooz * x * 2);
	yp = static_cast<int>(height / 2 + K1 * ooz * y);

	idx = xp + yp * width;
	if (idx >= 0 && idx < width * height) {
		if (ooz > zBuffer[idx]) {
			zBuffer[idx] = ooz;
			buffer[idx] = ch;
		}
	}
}

int main() {
	cout << "\x1b[2J";
	while (true) {
		memset(buffer, backgroundASCIICode, width * height);
		memset(zBuffer, 0, width * height * 4);
		
		cubeWidth = 20;
		horizontalOffset = -2 * cubeWidth;
		//primeiro cubo
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
			for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
				calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
				calculateForSurface(cubeWidth, cubeY, cubeX, '$');
				calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
				calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
				calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
				calculateForSurface(cubeX, cubeWidth, cubeY, '+');
			}
		}
		cubeWidth = 10;
		horizontalOffset = 1 * cubeWidth;
		//segundo cubo
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
			for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
				calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
				calculateForSurface(cubeWidth, cubeY, cubeX, '$');
				calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
				calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
				calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
				calculateForSurface(cubeX, cubeWidth, cubeY, '+');
			}
		}
		cubeWidth = 5;
		horizontalOffset = 8 * cubeWidth;
		//terceiro cubo
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
			for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
				calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
				calculateForSurface(cubeWidth, cubeY, cubeX, '$');
				calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
				calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
				calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
				calculateForSurface(cubeX, cubeWidth, cubeY, '+');
			}
		}
		cout << "\x1b[H";
		for (int k = 0; k < width * height; k++) {
			cout << buffer[k];
			if (k % width == width - 1) {
				cout << endl;
			}
		}

		A += 0.5;
		B += 0.5;
		C += 0.1;
		std::this_thread::sleep_for(std::chrono::milliseconds(8000 * 2));
	}
	return 0;
}