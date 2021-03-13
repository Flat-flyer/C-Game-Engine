#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPos;

struct Light {
	vec3 position;
	float ambientValue;
	float diffuseValue;
	float specularValue;
	vec3 lightColor;

};

uniform sampler2D inputTexture;
uniform vec3 cameraPos;
uniform Light light;

out vec4 fColour;

void main(){
	vec3 ambient = light.ambientValue * texture(inputTexture, TexCoords).rgb * light.lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.diffuseValue) * texture(inputTexture, TexCoords).rgb * light.lightColor;

	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * light.specularValue) * light.lightColor;

	vec3 result = ambient + diffuse + specular;

	fColour = vec4(result, 1.0f);
}