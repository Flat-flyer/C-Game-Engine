#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource {
public:
	LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, float specularValue_, glm::vec3 lightColor_);
	~LightSource();

	glm::vec3 GetPosition() const;
	float getAmbient() const;
	float getDiffuse() const;
	float getSpecular() const;
	glm::vec3 getLightColor() const;

	void setPosition(glm::vec3 position_);
	void setAmbient(float ambientValue_);
	void setDiffuse(float diffuseValue_);
	void setSpecular(float specularValue_);
	void setLightColor(glm::vec3 lightColor_);

	
private:
	glm::vec3 position;
	float ambientValue;
	float diffuseValue;
	float specularValue;
	glm::vec3 lightColor;
};
#endif // !LIGHTSOURCE_H
