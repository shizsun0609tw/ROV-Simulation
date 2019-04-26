#define _CRT_SECURE_NO_WARNINGS
#include "BMPfile.h"

BMPfile::BMPfile() {}

BMPfile::BMPfile(const char* filename)
{
	int rowSize;
	unsigned char bgr[256][4];
	unsigned char buf[4 * 4096];
	FILE *fp = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, fp); // read the 54-byte header

	// extract image height and width from header
	width = *(int*)&info[18];
	height = *(int*)&info[22];

	data = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 4);

	rowSize = ((width * 3 + 3) >> 2) << 2;

	for (int i = 0; i < height; i++) {
		fread(buf, 1, rowSize, fp);
		for (int j = 0; j < width; j++) {
			data[i * width * 4 + j * 4] = buf[j * 3 + 2];
			data[i * width * 4 + j * 4 + 1] = buf[j * 3 + 1];
			data[i * width * 4 + j * 4 + 2] = buf[j * 3];
			data[i * width * 4 + j * 4 + 3] = 255;
			if (buf[j * 3 + 2] == buf[j * 3 + 1] && 
				buf[j * 3 + 2] == buf[j * 3] && 
				buf[j * 3 + 2] == 255) {
				data[i * width * 4 + j * 4 + 3] = 0;
			}
		}
	}

	fclose(fp);
}

BMPfile::~BMPfile()
{
}

int BMPfile::getHeight() { return height; }

int BMPfile::getWidth() { return width; }

unsigned char* BMPfile::getData() { return data; }
