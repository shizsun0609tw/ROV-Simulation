#version 430 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess;
};

struct dirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct pointLight{
    vec3 position;

    float constant;
    float linear;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct spotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 pos;
in vec4 vColor;
in vec2 textureCoord;
in vec3 vnormal;

out vec4 color;

uniform sampler2D myTexture;
uniform float useTexture;
uniform Material myMaterial;
uniform dirLight myDiretionLight;
uniform pointLight myPointLight;
uniform spotLight mySpotLight;
uniform vec3 eyePos;

vec3 CalcDirLight(dirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);

	vec3 ambient = light.ambient * myMaterial.ambient;
	vec3 diffuse = light.diffuse * myMaterial.diffuse * max(dot(normal, lightDir), 0.0);
	vec3 specular = light.specular * myMaterial.specular * pow(max(dot(viewDir, reflectDir), 0.0), myMaterial.shininess);

    return (ambient + diffuse + specular);
} 

vec3 CalcPointLight(pointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance);   

	vec3 ambient = light.ambient * myMaterial.ambient;
	vec3 diffuse = light.diffuse * myMaterial.diffuse * max(dot(normal, lightDir), 0.0);
	vec3 specular = light.specular * myMaterial.specular * pow(max(dot(viewDir, reflectDir), 0.0), myMaterial.shininess);

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(spotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.f, 1.f);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance);   
    
	vec3 ambient = light.ambient * myMaterial.ambient;
	vec3 diffuse = light.diffuse * myMaterial.diffuse * max(dot(normal, lightDir), 0.0);
	vec3 specular = light.specular * myMaterial.specular * pow(max(dot(viewDir, reflectDir), 0.0), myMaterial.shininess);

    return (ambient + diffuse + specular) * attenuation * intensity;
}

void main(){
    vec3 normal = normalize(vnormal);
    vec3 viewDir = normalize(eyePos - pos);
    
    vec3 result = CalcPointLight(myPointLight, normal, pos, viewDir) 
                + CalcDirLight(myDiretionLight, normal, viewDir)
                + CalcSpotLight(mySpotLight, normal, pos, viewDir);

    color = vec4(result + myMaterial.emission, 1.f) * mix(vColor, texture(myTexture, textureCoord), useTexture);
}
