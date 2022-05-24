#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec2.hpp>

class Camera {
	glm::vec2 position;

	public:

		Camera();
		void setX(float x);
		void setY(float y);
		void setPosition(glm::vec2);
		float getX();
		float getY();
};

#endif