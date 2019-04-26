#pragma once

#include<fstream>
#include<iostream>

class BMPfile
{
public:
	BMPfile();
	BMPfile(const char* filename);
	~BMPfile();
	unsigned char* getData();
	int getWidth();
	int getHeight();
private:
	unsigned char* data;
	int width;
	int height;
};

