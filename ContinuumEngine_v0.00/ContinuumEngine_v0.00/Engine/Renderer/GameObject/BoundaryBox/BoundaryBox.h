#ifndef BoundaryBox_H
#define BoundaryBox_H

#include <glm/glm.hpp>


struct BoundaryBox {
	glm::vec3 minVert;
	glm::vec3 maxVert;
	glm::mat4 transform;


	inline BoundaryBox() {
		minVert = glm::vec3(0.0f);
		maxVert = glm::vec3(0.0f);
		transform = glm::mat4(0.0f);
	}


	inline BoundaryBox(glm::vec3 minVert_, glm::vec3 maxVert_, glm::mat4 transform_) {
		minVert = minVert_;
		maxVert_ = maxVert_;
		transform = transform_;
	}
};


#endif

