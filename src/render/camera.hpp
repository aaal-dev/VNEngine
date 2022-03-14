#pragma once

#include "../maths/maths.hpp"

class Camera {
public:
	enum CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	
	// ---------------------------------------------------- public.variables -- 
	vec3 position {0.0f, 0.0f, 0.0f};
	vec3 front {0.0f, 0.0f, -1.0f};
	vec3 right;
	vec3 up {0.0f, 1.0f, 0.0f};
	vec3 worldUp;
	float fov {90.0f};
	float aspectRatio {1.7777778f};
	float nearPlane {0.1f};
	float farPlane {100.0f};
	float yaw {0.0f};
	float pitch {0.0f};
	float movementSpeed {0.0025f};
	
	mat4 projectionMatrix;
	mat4 orthographicMatrix;
	mat4 perspectiveMatrix;
	mat4 lookAtMatrix {1.0f};
	vec3 pointAtVector;
	vec2 screenPoint {0.0f, 0.0f};
	
	// ---------------------------------------------------- public.functions -- 
	void update();
	void calculate();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	mat4 lookAt(const vec3 &position, const vec3 &target, const vec3 &worldUp);
	mat4 lookAt(const vec3 &position, const vec3 &direction, const vec3 &right, const vec3 &up);
	vec3 pointAt(float mouseScreenX, float mouseScreenY);
	vec3 pointAt(vec2 mouseScreenPosition);
	
	
private:
	void OnKeyPressed();
	
	
	
public:
	Camera();
	Camera(vec3 position, vec3 up, float yaw, float pitch);
	Camera(float posX, float posY, float posZ, 
	       float upX, float upY, float upZ, float yaw, float pitch);
	~Camera();
};
