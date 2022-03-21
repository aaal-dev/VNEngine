#include "camera.hpp"

// ------------------------------------------------------------------ Camera -- 

Camera::Camera () {
    orthographicMatrix = mat4::orthographic(0, 16.f, 0, 9.0f, -nearPlane, -farPlane);
    perspectiveMatrix = mat4::perspective(fov, aspectRatio, nearPlane, farPlane);
}

Camera::Camera (vec3 position, vec3 up, float yaw, float pitch)
: position(position), worldUp(up), yaw(yaw), pitch(pitch) {
  calculate();
}
Camera::Camera
(float posX, float posY, float posZ,
 float upX,  float upY,  float upZ,
 float yaw,  float pitch)
: position(posX, posY, posZ), worldUp(upX, upY, upZ), yaw(yaw),
  pitch(pitch) {
    calculate();
}

Camera::~Camera () {}

// ----------------------------------------------------------- public:Camera -- 

void Camera::update () {
//	movementSpeed = 2.5f * timeManager->deltaTime();
//	aspectRatio = controlManager->screen.aspectRatio;

//	if (controlManager->keyboard.key[KEY_W] == true) {
//		moveForward();
//	}
//	if (controlManager->keyboard.key[KEY_S] == true) {
//		moveBackward();
//	}
//	if (controlManager->keyboard.key[KEY_A] == true) {
//		moveLeft();
//	}
//	if (controlManager->keyboard.key[KEY_D] == true) {
//		moveRight();
//	}
	
//	yaw += controlManager->mouse.offsetx;
//	pitch += controlManager->mouse.offsety;
	if(yaw > 89.0f)
		yaw =  89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
//	screenPoint = controlManager->mouse.screenPosition;


    calculate();
    perspectiveMatrix = mat4::perspective(fov, aspectRatio, nearPlane, farPlane);
//lookAtMatrix = mat4::lookAt(position, front, right, up);
    lookAtMatrix = lookAt(position, position + front, worldUp);
    pointAtVector = pointAt(screenPoint);
}

void Camera::calculate () {
    vec3 vector;
    vector.x = cos(toRadians(yaw)) * cos(toRadians(pitch));
    vector.y = sin(toRadians(pitch));
    vector.z = sin(toRadians(yaw)) * cos(toRadians(pitch));
    front = vec3::normalize(vector);

// also re-calculate the Right and Up vector
//right = vec3::normalize(vec3::cross(front, worldUp));
//up    = vec3::normalize(vec3::cross(right, front));
}

/***
 * Create an look at point view matrix.
 * @param pos    [vec3] Position of the viewer's point (a "camera")
 * @param tar    [vec3] Position of the target point
 * @param upSign [vec3] Determinate up direction
 * @return       [mat4] The perspective transformation matrix
 * */
mat4 Camera::lookAt (const vec3 &pos, const vec3 &tar, const vec3 &upSign) {
    vec3 direction = vec3::normalize(pos - tar);
    vec3 right = vec3::normalize(vec3::cross(upSign, direction));
    vec3 up = vec3::cross(direction, right);

/*mat4 mat4::lookAt (const vec3 &pos, 
                   const vec3 &direction, 
                   const vec3 &right, 
                   const vec3 &up) {*/
	mat4 result;
	     result.elements[0]  =     right.x;                   // row: 0, col: 0
	     result.elements[1]  =        up.x;                   // row: 1, col: 0
	     result.elements[2]  = direction.x;                   // row: 2, col: 0
	     result.elements[4]  =     right.y;                   // row: 0, col: 1
	     result.elements[5]  =        up.y;                   // row: 1, col: 1
	     result.elements[6]  = direction.y;                   // row: 2, col: 1
	     result.elements[8]  =     right.z;                   // row: 0, col: 2
	     result.elements[9]  =        up.z;                   // row: 1, col: 2
	     result.elements[10] = direction.z;                   // row: 2, col: 2
	     result.elements[12] =     right.x * -pos.x           // row: 0, col: 3
	                         +     right.y * -pos.y
	                         +     right.z * -pos.z;
	     result.elements[13] =        up.x * -pos.x           // row: 1, col: 3
	                         +        up.y * -pos.y
	                         +        up.z * -pos.z;
	     result.elements[14] = direction.x * -pos.x           // row: 2, col: 3
	                         + direction.y * -pos.y
	                         + direction.z * -pos.z;
	     result.elements[15] = 1.0f;                          // row: 3, col: 3
	
	return result;
}

vec3 Camera::pointAt (float mouseScreenX, float mouseScreenY) {
    mat4 invVP = mat4::inverse(perspectiveMatrix * lookAtMatrix);
    vec4 screenPos = vec4(mouseScreenX, mouseScreenY, -1.0f, 1.0f);
    vec4 worldPos = invVP * screenPos;
    return vec3::normalize(vec3(worldPos.x, worldPos.y, worldPos.z));
}

vec3 Camera::pointAt (vec2 mouseScreenPosition) {
    return pointAt(mouseScreenPosition.x, mouseScreenPosition.y);
}

void Camera::moveForward () {
    position += front * movementSpeed;
}

void Camera::moveBackward () {
    position -= front * movementSpeed;
}

void Camera::moveLeft () {
    position -= right * movementSpeed;
}

void Camera::moveRight () {
    position += right * movementSpeed;
}

void Camera::moveUp () {
    position += up * movementSpeed;
}

void Camera::moveDown () {
    position -= up * movementSpeed;
}

