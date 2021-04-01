#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

struct Light {
	vec3 position;
	float ambientValue;
	float diffuseValue;
	float specularValue;
	vec3 lightColor;

};

struct Material {
	sampler2D diffuseMap; //newmtl

	float shininess; //Ns
	float transparency; //d

	vec3 ambient; //Ka
	vec3 diffuse; //Kd
	vec3 specular; //Ks
};

uniform vec3 cameraPos;
uniform Light light;
uniform Material material;

out vec4 fColour;

void main(){
	vec3 ambient = light.ambientValue * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColor;

	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColor;

	vec3 result = ambient + diffuse + specular;

	fColour = vec4(result, material.transparency);
}