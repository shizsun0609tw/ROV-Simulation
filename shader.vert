#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;

out vec4 vColor;
out vec2 textureCoord;
out vec3 vnormal;
out vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

void main(){
    gl_Position = projection * view * model * vec4(position, 1.f);
    pos = vec3(model * vec4(position, 1.f)); 

    vColor = color;
    textureCoord = texture;

    mat3 normalMatrix = mat3(transpose(inverse(model)));
	vnormal = normalMatrix * normal;
}
