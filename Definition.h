#pragma once

#include "glm/glm.hpp"

#define DISPLAY_MODE0 0
#define DISPLAY_MODE1 1
#define DISPLAY_MODE2 2
#define DISPLAY_MODE3 3
#define DISPLAY_MODE4 4

#define CONTROL_EYE 0
#define CONTROL_ROV 1 
#define CONTROL_LIGHT 2

#define DIRECIONAL_LIGHT 0
#define POINT_LIGHT 1
#define ROV_LIGHT 2

#define LIGHT_OFF 0
#define LIGHT_ON 1

#define OBSTACLE_NUM 3

#define TEX_NUM 103
#define SCENE_NUM 5
#define FISH_NUM 8
#define GRASS_NUM 40
#define JELLYFISH_NUM 50

#define KEY_NULL -1
#define KEY_W 0
#define KEY_A 1
#define KEY_S 2
#define KEY_D 3
#define KEY_Q 4
#define KEY_E 5


using namespace std;

struct material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};


const static float viewVolumnNear = 0.1f;
const static float viewVolumnFar = 500.f;

const static glm::vec3 noLight(0.f, 0.f, 0.f);

const static glm::vec4 rock(0.29f, 0.27f, 0.23f, 1.f);
const static glm::vec4 yellow(0.91f, 0.67f, 0.15f, 1.f);
const static glm::vec4 green(0.1f, 0.8f, 0.1f, 1.f);
const static glm::vec4 blue(0.1f, 0.1f, 0.8f, 1.f);
const static glm::vec4 red(0.8f, 0.1f, 0.1f, 1.f);
const static glm::vec4 white(1.f, 1.f, 1.f, 1.f);

const static float terrainWidth = 200.f, terrainHeight = 200.f, terrainDepth = 30.f;

const static material no_mat = { glm::vec3(0.f, 0.f, 0.f),
								 glm::vec3(0.f, 0.f, 0.f),
								 glm::vec3(0.f, 0.f, 0.f), 0.f };
const static material silver = { glm::vec3(0.19225f, 0.19225f, 0.19225f),
								 glm::vec3(0.50754f, 0.50754f, 0.50754f),
								 glm::vec3(0.508273f, 0.508273f, 0.508273f), 512.f};
const static material whitePlastic = { glm::vec3(0.0f,0.0f,0.0f),
								 glm::vec3(0.55f,0.55f,0.55f),
								 glm::vec3(0.70f,0.70f,0.70f), 32.0f };
const static material ruby = { glm::vec3(0.1745f, 0.01175f, 0.01175f),
								 glm::vec3(0.61424f, 0.04136f, 0.04136f),
								 glm::vec3(0.727811f, 0.626959f, 0.626959f), 76.8f };
const static material emerald = { glm::vec3(0.0215f, 0.1745f, 0.0215f),
								 glm::vec3(0.07568f, 0.61424f, 0.07568f),
								 glm::vec3(0.633f, 0.727811f, 0.633f), 76.8f };
const static material cyanPlastic = { glm::vec3(0.0f,0.1f,0.06f),
								 glm::vec3(0.0f,0.50980392f,0.50980392f),
								 glm::vec3(0.50196078f,0.50196078f,0.50196078f), 32.f };
const static material perl = { glm::vec3(0.25f, 0.20725f, 0.20725f),
								 glm::vec3(1.0f, 0.829f, 0.829f),
								 glm::vec3(0.296648f, 0.296648f, 0.296648f), 11.264f };
const static material brass = { glm::vec3(0.329412f, 0.223529f, 0.027451f),
								 glm::vec3(0.780392f, 0.568627f, 0.113725f),
								 glm::vec3(0.992157f, 0.941176f, 0.807843f), 27.8974f };
const static material obsidian = { glm::vec3(0.05375f, 0.05f, 0.06625f),
								 glm::vec3(0.18275f, 0.17f, 0.22525f),
								 glm::vec3(0.332741f, 0.328634f, 0.346435f), 38.4f };
