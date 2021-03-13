#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, float specularValue_, glm::vec3 lightColor_)
{
	position = position_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
	specularValue = specularValue_;
	lightColor = lightColor_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const
{
	return position;
}

float LightSource::getAmbient() const
{
	return ambientValue;
}

float LightSource::getDiffuse() const
{
	return diffuseValue;
}

float LightSource::getSpecular() const
{
	return specularValue;
}

glm::vec3 LightSource::getLightColor() const
{
	return lightColor;
}

void LightSource::setPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::setAmbient(float ambientValue_)
{
	ambientValue = ambientValue_;
}

void LightSource::setDiffuse(float diffuseValue_)
{
	diffuseValue = diffuseValue_;
}

void LightSource::setSpecular(float specularValue_)
{
	specularValue = specularValue_;
}

void LightSource::setLightColor(glm::vec3 lightColor_)
{
	lightColor = lightColor_;
}
