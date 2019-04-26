#pragma once

#include "Definition.h"
#include <gl/glew.h>
#include "BMPfile.h"

class texture
{
public:
	texture();
	~texture();
	static GLuint myTexture[TEX_NUM];
	static void init();
private:
	static BMPfile sceneArr[SCENE_NUM];
	static BMPfile fishArr[FISH_NUM];
	static BMPfile grassArr[GRASS_NUM];
	static BMPfile jellyFishArr[JELLYFISH_NUM];
};

