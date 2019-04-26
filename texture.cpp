#include "texture.h"

texture::texture()
{

}


texture::~texture()
{
}

void texture::init() {
	sceneArr[0] = BMPfile("texture/rock.bmp");
	sceneArr[1] = BMPfile("texture/sand.bmp");
	sceneArr[2] = BMPfile("texture/metal.bmp");
	sceneArr[3] = BMPfile("texture/light.bmp");
	sceneArr[4] = BMPfile("texture/sea.bmp");
	for (int i = 0; i < FISH_NUM; i++) {
		fishArr[i] = BMPfile("texture/fish0.bmp");
	}
	for (int i = 0; i < GRASS_NUM; i++) {
		grassArr[i] = BMPfile("texture/grass.bmp");
	}

	for (int i = 0; i < JELLYFISH_NUM; i++) {
		jellyFishArr[i] = BMPfile("texture/jellyfish.bmp");
	}

	int count = 0;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(TEX_NUM, myTexture);
	for (int i = 0; i < SCENE_NUM; i++, count++) {
		glBindTexture(GL_TEXTURE_2D, myTexture[count]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sceneArr[i].getWidth(), sceneArr[i].getHeight(), 0, GL_RGBA,
			GL_UNSIGNED_BYTE, sceneArr[i].getData());
	}
	for (int i = 0; i < FISH_NUM; i++, count++) {

		glBindTexture(GL_TEXTURE_2D, myTexture[count]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fishArr[i].getWidth(), fishArr[i].getHeight(), 0, GL_RGBA,
			GL_UNSIGNED_BYTE, fishArr[i].getData());
	}
	for (int i = 0; i < GRASS_NUM; i++, count++) {

		glBindTexture(GL_TEXTURE_2D, myTexture[count]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, grassArr[i].getWidth(), grassArr[i].getHeight(), 0, GL_RGBA,
			GL_UNSIGNED_BYTE, grassArr[i].getData());
	}
	for (int i = 0; i < JELLYFISH_NUM; i++, count++) {

		glBindTexture(GL_TEXTURE_2D, myTexture[count]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, jellyFishArr[i].getWidth(), jellyFishArr[i].getHeight(), 0, GL_RGBA,
			GL_UNSIGNED_BYTE, jellyFishArr[i].getData());
	}
}


GLuint texture::myTexture[TEX_NUM];
BMPfile texture::sceneArr[SCENE_NUM];
BMPfile texture::fishArr[FISH_NUM];
BMPfile texture::grassArr[GRASS_NUM];
BMPfile texture::jellyFishArr[JELLYFISH_NUM];