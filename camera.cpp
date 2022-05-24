#include "camera.h"

Camera::Camera(){}

void Camera::setX(float x){
	this->position.x = x;
}

void Camera::setY(float y){
	this->position.y = y;
}

void Camera::setPosition(glm::vec2 position){
	this->position = position;
}

float Camera::getX(){
	return this->position.x;
}

float Camera::getY(){
	return this->position.y;
}
