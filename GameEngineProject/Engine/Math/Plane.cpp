#include "Plane.h"
#include <stdio.h>
#include <iostream>

Plane::Plane(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3)
{
	d = 0;
	set3Points(v1, v2, v3);
}

Plane::Plane()
{
	d = 0;
}

Plane::~Plane()
{
}

void Plane::set3Points(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3)
{
	glm::vec3 aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	normal = aux2 * aux1;

	normal = glm::normalize(normal);
	point = v2;
	d = -(normal.x * point.x + normal.y * point.y + normal.z * point.z);
}

void Plane::setNormalAndPoint(glm::vec3& normal_, glm::vec3& point_)
{
	normal = normal_;
	normal = glm::normalize(normal);
}

void Plane::setCoefficients(float a_, float b_, float c_, float d_)
{
	// set the normal vector
	normal = glm::vec3(a_, b_, c_);
	//compute the lenght of the vector
	float l = normal.length();
	// normalize the vector
	normal = glm::vec3(a_ / l, b_ / l, c_ / l);
	// and divide d by th length as well
	this->d = d / l;
}

float Plane::distance(glm::vec3& p_)
{
	return (d + (normal.x * p_.x + normal.y * p_.y + normal.z * p_.z));
}

void Plane::print()
{
	std::cout << "Plane(" << glm::to_string(normal) << " # " << d ;
}
