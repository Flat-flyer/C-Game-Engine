#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

struct BoundingBox {
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;

	inline BoundingBox() {
		maxVert = minVert = glm::vec3();
		transform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_) {
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_) {
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		glm::vec3 otherMinCorner = GetTransformedPoint(box_->minVert, box_->transform);
		glm::vec3 otherMaxCorner = GetTransformedPoint(box_->maxVert, box_->transform);

		//BLR
		if (minCorner.x > otherMinCorner.x && minCorner.x < otherMaxCorner.x && minCorner.y > otherMinCorner.y && minCorner.y < otherMaxCorner.y && minCorner.z > otherMinCorner.z && minCorner.z < otherMaxCorner.z) {
			return true;
		}
		//TRF
		else if (maxCorner.x > otherMinCorner.x && maxCorner.x < otherMaxCorner.x && maxCorner.y > otherMinCorner.y && maxCorner.y < otherMaxCorner.y && maxCorner.z > otherMinCorner.z && maxCorner.z < otherMaxCorner.z) {
			return true;
		}
		//TLR
		else if (minCorner.x > otherMinCorner.x && minCorner.x < otherMaxCorner.x && maxCorner.y > otherMinCorner.y && maxCorner.y < otherMaxCorner.y && minCorner.z > otherMinCorner.z && minCorner.z < otherMaxCorner.z) {
			return true;
		}
		//TLF
		else if (minCorner.x > otherMinCorner.x && minCorner.x < otherMaxCorner.x && maxCorner.y > otherMinCorner.y && maxCorner.y < otherMaxCorner.y && maxCorner.z > otherMinCorner.z && maxCorner.z < otherMaxCorner.z) {
			return true;
		}
		//TRR
		else if (maxCorner.x > otherMinCorner.x && maxCorner.x < otherMaxCorner.x && maxCorner.y > otherMinCorner.y && maxCorner.y < otherMaxCorner.y && minCorner.z > otherMinCorner.z && minCorner.z < otherMaxCorner.z) {
			return true;
		}
		//BRR
		else if (maxCorner.x > otherMinCorner.x && maxCorner.x < otherMaxCorner.x && minCorner.y > otherMinCorner.y && minCorner.y < otherMaxCorner.y && minCorner.z > otherMinCorner.z && minCorner.z < otherMaxCorner.z) {
			return true;
		}
		//BRF
		else if (maxCorner.x > otherMinCorner.x && maxCorner.x < otherMaxCorner.x && minCorner.y > otherMinCorner.y && minCorner.y < otherMaxCorner.y && maxCorner.z > otherMinCorner.z && maxCorner.z < otherMaxCorner.z) {
			return true;
		}
		//BLF
		else if (minCorner.x > otherMinCorner.x && minCorner.x < otherMaxCorner.x && minCorner.y > otherMinCorner.y && minCorner.y < otherMaxCorner.y && maxCorner.z > otherMinCorner.z && maxCorner.z < otherMaxCorner.z) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_) {
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};

#endif // !BOUNDINGBOX_H

