#ifndef _PLANE_
#define _PLANE_

#ifndef _Vec3_
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#endif

class Plane
{

public:

	glm::vec3 normal, point;
	float d;


	Plane(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3);
	Plane();
	~Plane();

	void set3Points(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3);
	void setNormalAndPoint(glm::vec3& normal_, glm::vec3& point_);
	void setCoefficients(float a_, float b_, float c_, float d_);
	float distance(glm::vec3& p_);

	void print();

};


#endif
