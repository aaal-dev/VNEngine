

#include "mat4.hpp"



// index = row + col * 4

// -------------------------------------------------------------------- mat4 -- 

mat4::mat4 () {}

mat4::mat4 (float diagonal) {
	elements[0]  = diagonal;                                  // row: 0, col: 0
	elements[5]  = diagonal;                                  // row: 1, col: 1
	elements[10] = diagonal;                                  // row: 2, col: 2
	elements[15] = diagonal;                                  // row: 3, col: 3
}

mat4::mat4 (float elements[16]) {
	for (unsigned int i = 0; i < 16; i++)
		this->elements[i] = elements[i];
}

// -------------------------------------------------------------------- mat4 -- 

/***
 * Create an identity matrix.
 * @return       [mat4]  The identity matrix
 * */
mat4 mat4::identity () {
	mat4 result;
	
	result.elements[0]  = 1.0f;                               // row: 0, col: 0
	result.elements[5]  = 1.0f;                               // row: 1, col: 1
	result.elements[10] = 1.0f;                               // row: 2, col: 2
	result.elements[15] = 1.0f;                               // row: 3, col: 3
	
	return result;
}


/***
 * Create an orthographic projection matrix.
 * @param left   [float] Farthest left on the x-axis
 * @param right  [float] Farthest right on the x-axis
 * @param bottom [float] Farthest down on the y-axis
 * @param top    [float] Farthest up on the y-axis
 * @param near   [float] Distance to the near clipping plane along the -Z axis
 * @param far    [float] Distance to the far clipping plane along the -Z axis
 * @return       [mat4]  The orthographic transformation matrix
 * */
mat4 mat4::orthographic (float left, float right, 
                         float bottom, float top,
                         float near, float far) {
	mat4 result;
	
	float lr = 1.0f / (left - right);
	float bt = 1.0f / (bottom - top);
	float nf = 1.0f / (near - far);
	
	result.elements[0]  = -2.0f * lr;                         // row: 0, col: 0
	result.elements[5]  = -2.0f * bt;                         // row: 1, col: 1
	result.elements[10] =  2.0f * nf;                         // row: 2, col: 2
	result.elements[12] =  (right + left) * lr;               // row: 0, col: 3
	result.elements[13] =  (top + bottom) * bt;               // row: 1, col: 3
	result.elements[14] =  (far + near) * nf;                 // row: 2, col: 3
	result.elements[15] =  1.0f;                              // row: 3, col: 3
	
	return result;
}

/***
 * Create an perspective projection matrix.
 * @param fov    [float] Angle of field of view
 * @param aspect [float] Aspect ratio of field of view
 * @param near   [float] Distance to the near clipping plane along the -Z axis
 * @param far    [float] Distance to the far clipping plane along the -Z axis
 * @return       [mat4]  The perspective transformation matrix
 * */
mat4 mat4::perspective (float fov, float aspect, float near, float far) {
	mat4 result;
	
	float nf = 1.0f / (near - far);
	
	fov = tan(toRadians(90.0f - 0.5f * fov));
	
	result.elements[0]  =  fov / aspect;                      // row: 0, col: 0
	result.elements[5]  =  fov;                               // row: 1, col: 1
	result.elements[10] =  (far + near) * nf;                 // row: 2, col: 2
	result.elements[11] = -1.0f;                              // row: 2, col: 3
	result.elements[14] =  2 * far * near * nf;               // row: 3, col: 2
	
	return result;
}

/***
 * Create a rotation transformation matrix.
 * @param angle  [float] Angle of rotation
 * @param v      [vec3]  Vector of point
 * @return       [mat4]  The rotation transformation matrix
 * */
mat4 mat4::rotation (float angle, const vec3 &v) {
	mat4 result;
	
	angle = toRadians(angle);
	
	float cosinus = cos(angle);
	float sinus = sin(angle);
	float rcos = 1.0f - cosinus;
	
	result.elements[0]  = v.x * v.x * rcos + cosinus;         // row: 0, col: 0
	result.elements[1]  = v.x * v.y * rcos - v.z * sinus;     // row: 1, col: 0
	result.elements[2]  = v.x * v.z * rcos + v.y * sinus;     // row: 2, col: 0
	result.elements[4]  = v.y * v.x * rcos + v.z * sinus;     // row: 0, col: 1
	result.elements[5]  = v.y * v.y * rcos + cosinus;         // row: 1, col: 1
	result.elements[6]  = v.y * v.z * rcos - v.x * sinus;     // row: 2, col: 1
	result.elements[8]  = v.z * v.x * rcos - v.y * sinus;     // row: 0, col: 2
	result.elements[9]  = v.z * v.y * rcos + v.x * sinus;     // row: 1, col: 2
	result.elements[10] = v.z * v.z * rcos + cosinus;         // row: 2, col: 2
	result.elements[15] = 1.0f;                               // row: 3, col: 3
	
	return result;
}

/***
 * Create a rotation transformation matrix.
 * @param angle  [float]         Angle of rotation
 * @param axis   [RotationAxis]  Enum of rotation axis
 * @return       [mat4]          The rotation transformation matrix
 * */
mat4 mat4::rotation (float angle, RotationAxis axis) {
	mat4 result;
	
	switch (axis) {
		case ROTATION_X:
			result = rotation(angle, vec3(1,0,0));
			break;
		case ROTATION_Y:
			result = rotation(angle, vec3(0,1,0));
			break;
		case ROTATION_Z:
			result = rotation(angle, vec3(0,0,1));
			break;
	}
	return result;
}

/***
 * Create a scale transformation matrix.
 * @param v      [vec3]  Vector of scale ratio
 * @return       [mat4]  The scale transformation matrix
 * */
mat4 mat4::scale (const vec3 &v) {
	mat4 result;
	
	result.elements[0]  = v.x;                                // row: 0, col: 0
	result.elements[5]  = v.y;                                // row: 1, col: 1
	result.elements[10] = v.z;                                // row: 2, col: 2
	result.elements[15] = 1.0f;                               // row: 3, col: 3
	
	return result;
}

/***
 * Create a translation transformation matrix.
 * @param v      [vec3]  Vector of distance to traslate
 * @return       [mat4]  The translation transformation matrix
 * */
mat4 mat4::translation (const vec3 &v) {
	mat4 result;
	
	result.elements[0]  = 1.0f;                               // row: 0, col: 0
	result.elements[5]  = 1.0f;                               // row: 1, col: 1
	result.elements[10] = 1.0f;                               // row: 2, col: 2
	result.elements[12] = v.x;                                // row: 0, col: 3
	result.elements[13] = v.y;                                // row: 1, col: 3
	result.elements[14] = v.z;                                // row: 2, col: 3
	result.elements[15] = 1.0f;                               // row: 3, col: 3
	
	return result;
}

/***
 * Create a inverse matrix.
 * @param m      [mat4]  Matrix to inverse
 * @return       [mat4]  The inversed matrix
 * */
mat4 mat4::inverse(const mat4 &m) {
	float results[16];
	results[0]  = m.elements[5]  * m.elements[10] * m.elements[15] // results[0]
	            - m.elements[6]  * m.elements[9]  * m.elements[15] 
	            + m.elements[5]  * m.elements[11] * m.elements[14] 
	            - m.elements[7]  * m.elements[9]  * m.elements[14] 
	            + m.elements[6]  * m.elements[11] * m.elements[13] 
	            - m.elements[7]  * m.elements[10] * m.elements[13];
	results[1]  = m.elements[1]  * m.elements[11] * m.elements[14] // results[1]
	            - m.elements[1]  * m.elements[10] * m.elements[15] 
	            + m.elements[2]  * m.elements[9]  * m.elements[15] 
	            - m.elements[3]  * m.elements[9]  * m.elements[14] 
	            + m.elements[3]  * m.elements[13] * m.elements[10] 
	            - m.elements[2]  * m.elements[13] * m.elements[11];
	results[2]  = m.elements[1]  * m.elements[6]  * m.elements[15] // results[2]
	            - m.elements[1]  * m.elements[7]  * m.elements[14] 
	            + m.elements[3]  * m.elements[5]  * m.elements[14] 
	            - m.elements[2]  * m.elements[5]  * m.elements[15] 
	            + m.elements[2]  * m.elements[7]  * m.elements[13] 
	            - m.elements[3]  * m.elements[6]  * m.elements[13];
	results[3]  = m.elements[1]  * m.elements[7]  * m.elements[10] // results[3]
	            - m.elements[1]  * m.elements[6]  * m.elements[11] 
	            + m.elements[5]  * m.elements[2]  * m.elements[11] 
	            - m.elements[5]  * m.elements[3]  * m.elements[10] 
	            + m.elements[9]  * m.elements[3]  * m.elements[6]  
	            - m.elements[9]  * m.elements[2]  * m.elements[7] ;
	results[4]  = m.elements[4]  * m.elements[11] * m.elements[14] // results[4]
	            - m.elements[4]  * m.elements[10] * m.elements[15] 
	            + m.elements[8]  * m.elements[6]  * m.elements[15] 
	            - m.elements[8]  * m.elements[7]  * m.elements[14] 
	            + m.elements[12] * m.elements[7]  * m.elements[10] 
	            - m.elements[12] * m.elements[6]  * m.elements[11];
	results[5]  = m.elements[0]  * m.elements[10] * m.elements[15] // results[5]
	            - m.elements[0]  * m.elements[11] * m.elements[14] 
	            + m.elements[8]  * m.elements[3]  * m.elements[14] 
	            - m.elements[8]  * m.elements[2]  * m.elements[15] 
	            + m.elements[12] * m.elements[2]  * m.elements[11] 
	            - m.elements[12] * m.elements[3]  * m.elements[10];
	results[6]  = m.elements[0]  * m.elements[7]  * m.elements[14] // results[6]
	            - m.elements[0]  * m.elements[6]  * m.elements[15] 
	            + m.elements[4]  * m.elements[2]  * m.elements[15] 
	            - m.elements[4]  * m.elements[3]  * m.elements[14] 
	            + m.elements[3]  * m.elements[6]  * m.elements[12] 
	            - m.elements[2]  * m.elements[7]  * m.elements[12];
	results[7]  = m.elements[0]  * m.elements[6]  * m.elements[11] // results[7]
	            - m.elements[0]  * m.elements[7]  * m.elements[10] 
	            + m.elements[4]  * m.elements[3]  * m.elements[10] 
	            - m.elements[4]  * m.elements[2]  * m.elements[11] 
	            + m.elements[8]  * m.elements[2]  * m.elements[7] 
	            - m.elements[8]  * m.elements[3]  * m.elements[6] ;
    results[8]  = m.elements[4]  * m.elements[9]  * m.elements[15] // results[8]
	            - m.elements[4]  * m.elements[11] * m.elements[13] 
	            + m.elements[8]  * m.elements[7]  * m.elements[13] 
	            - m.elements[8]  * m.elements[5]  * m.elements[15] 
	            + m.elements[12] * m.elements[5]  * m.elements[11] 
	            - m.elements[12] * m.elements[7]  * m.elements[9] ;
	results[9]  = m.elements[0]  * m.elements[11] * m.elements[13] // results[9]
	            - m.elements[0]  * m.elements[9]  * m.elements[15] 
	            + m.elements[8]  * m.elements[1]  * m.elements[15] 
	            - m.elements[8]  * m.elements[3]  * m.elements[13] 
	            + m.elements[3]  * m.elements[9]  * m.elements[12]
	            - m.elements[1]  * m.elements[11] * m.elements[12];
	results[10] = m.elements[0]  * m.elements[5]  * m.elements[15] // results[10]
	            - m.elements[0]  * m.elements[7]  * m.elements[13] 
	            + m.elements[4]  * m.elements[3]  * m.elements[13] 
	            - m.elements[4]  * m.elements[1]  * m.elements[15] 
	            + m.elements[1]  * m.elements[7]  * m.elements[12] 
	            - m.elements[3]  * m.elements[5]  * m.elements[12];
	results[11] = m.elements[0]  * m.elements[7]  * m.elements[9]  // results[11]
	            - m.elements[0]  * m.elements[5]  * m.elements[11] 
	            + m.elements[4]  * m.elements[1]  * m.elements[11] 
	            - m.elements[4]  * m.elements[3]  * m.elements[9] 
	            + m.elements[8]  * m.elements[3]  * m.elements[5]
	            - m.elements[8]  * m.elements[1]  * m.elements[7] ;
	results[12] = m.elements[4]  * m.elements[10] * m.elements[13] // results[12]
	            - m.elements[4]  * m.elements[9]  * m.elements[14] 
	            + m.elements[8]  * m.elements[5]  * m.elements[14] 
	            - m.elements[8]  * m.elements[6]  * m.elements[13] 
	            + m.elements[12] * m.elements[6]  * m.elements[9]
	            - m.elements[12] * m.elements[5]  * m.elements[10];
	results[13] = m.elements[0]  * m.elements[9]  * m.elements[14] // results[13]
	            - m.elements[0]  * m.elements[10] * m.elements[13] 
	            + m.elements[8]  * m.elements[2]  * m.elements[13]
	            - m.elements[8]  * m.elements[1]  * m.elements[14] 
	            + m.elements[1]  * m.elements[10] * m.elements[12] 
	            - m.elements[2]  * m.elements[9]  * m.elements[42];
	results[14] = m.elements[0]  * m.elements[6]  * m.elements[13] // results[14]
	            - m.elements[0]  * m.elements[5]  * m.elements[14] 
	            + m.elements[4]  * m.elements[1]  * m.elements[14] 
	            - m.elements[4]  * m.elements[2]  * m.elements[13] 
	            + m.elements[2]  * m.elements[5]  * m.elements[12]
	            - m.elements[1]  * m.elements[6]  * m.elements[12];
	results[15] = m.elements[0]  * m.elements[5]  * m.elements[10] // results[15]
	            - m.elements[0]  * m.elements[6]  * m.elements[9] 
	            + m.elements[4]  * m.elements[2]  * m.elements[9] 
	            - m.elements[4]  * m.elements[1]  * m.elements[10] 
	            + m.elements[8]  * m.elements[1]  * m.elements[6] 
	            - m.elements[8]  * m.elements[2]  * m.elements[5] ;
	
	float det = m.elements[0] * results[0] + m.elements[1] * results[4] 
	          + m.elements[2] * results[8] + m.elements[3] * results[12];
	
	if (det == 0) return mat4(1.0f);
	
	det = 1.0 / det;
	
	mat4 resultMat4;
	for (unsigned int i = 0; i < 16; i++)
		resultMat4.elements[i] = results[i] * det;
	
	return resultMat4;
}

// -------------------------------------------------------------------- mat4 -- 

/***
 * Multiply current matrix with another.
 * @param m      [mat4]  Another matrix
 * @return       [mat4]  The result of multiply matrices
 * */
mat4& mat4::multiply (const mat4 &m) {
	float data[16];
	data[0]  = elements[0]  * m.elements[0]  + elements[4]  * m.elements[1]  
	         + elements[8]  * m.elements[2]  + elements[12] * m.elements[3];
	data[1]  = elements[1]  * m.elements[0]  + elements[5]  * m.elements[1]  
	         + elements[9]  * m.elements[2]  + elements[13] * m.elements[3];
	data[2]  = elements[2]  * m.elements[0]  + elements[6]  * m.elements[1]  
	         + elements[10] * m.elements[2]  + elements[14] * m.elements[3];
	data[3]  = elements[3]  * m.elements[0]  + elements[7]  * m.elements[1]  
	         + elements[11] * m.elements[2]  + elements[15] * m.elements[3];
	
	data[4]  = elements[0]  * m.elements[4]  + elements[4]  * m.elements[5]  
	         + elements[8]  * m.elements[6]  + elements[12] * m.elements[7];
	data[5]  = elements[1]  * m.elements[4]  + elements[5]  * m.elements[5]  
	         + elements[9]  * m.elements[6]  + elements[13] * m.elements[7];
	data[6]  = elements[2]  * m.elements[4]  + elements[6]  * m.elements[5]  
	         + elements[10] * m.elements[6]  + elements[14] * m.elements[7];
	data[7]  = elements[3]  * m.elements[4]  + elements[7]  * m.elements[5]  
	         + elements[11] * m.elements[6]  + elements[15] * m.elements[7];
	
	data[8]  = elements[0]  * m.elements[8]  + elements[4]  * m.elements[9]  
	         + elements[8]  * m.elements[10] + elements[12] * m.elements[11];
	data[9]  = elements[1]  * m.elements[8]  + elements[5]  * m.elements[9]  
	         + elements[9]  * m.elements[10] + elements[13] * m.elements[11];
	data[10] = elements[2]  * m.elements[8]  + elements[6]  * m.elements[9]  
	         + elements[10] * m.elements[10] + elements[14] * m.elements[11];
	data[11] = elements[3]  * m.elements[8]  + elements[7]  * m.elements[9]  
	         + elements[11] * m.elements[10] + elements[15] * m.elements[11];
	
	data[12] = elements[0]  * m.elements[12] + elements[4]  * m.elements[13] 
	         + elements[8]  * m.elements[14] + elements[12] * m.elements[15];
	data[13] = elements[1]  * m.elements[12] + elements[5]  * m.elements[13] 
	         + elements[9]  * m.elements[14] + elements[13] * m.elements[15];
	data[14] = elements[2]  * m.elements[12] + elements[6]  * m.elements[13] 
	         + elements[10] * m.elements[14] + elements[14] * m.elements[15];
	data[15] = elements[3]  * m.elements[12] + elements[7]  * m.elements[13] 
	         + elements[11] * m.elements[14] + elements[15] * m.elements[15];
	
	memcpy(elements, data, 16 * sizeof(float));
	return *this;
}

/***
 * Multiply current matrix with vector of 3.
 * @param v      [vec3]  Vector of 3
 * @return       [vec3]  The result of multiply matrix and vector
 * */
vec3 mat4::multiply(const vec3 &v) const {
	float data[3];
	data[0] = elements[0]  * v.x + elements[4] * v.y 
	        + elements[8]  * v.z + elements[12];
	data[1] = elements[1]  * v.x + elements[5] * v.y 
	        + elements[9]  * v.z + elements[13];
	data[2] = elements[2]  * v.x + elements[6] * v.y 
	        + elements[10] * v.z + elements[14];
	return vec3(data);
}

/***
 * Multiply current matrix with vector of 4.
 * @param v      [vec4]  Vector of 4
 * @return       [vec4]  The result of multiply matrix and vector
 * */
vec4 mat4::multiply(const vec4 &v) const {
	float data[4];
	data[0]  = elements[0]  * v.x + elements[4]  * v.y 
	         + elements[8]  * v.z + elements[12] * v.w;
	data[1]  = elements[1]  * v.x + elements[5]  * v.y 
	         + elements[9]  * v.z + elements[13] * v.w;
	data[2]  = elements[2]  * v.x + elements[6]  * v.y 
	         + elements[10] * v.z + elements[14] * v.w;
	data[3]  = elements[3]  * v.x + elements[7]  * v.y 
	         + elements[11] * v.z + elements[15] * v.w;
	return vec4(data);
}

// --------------------------------------------------------  mat4::operators -- 

mat4& mat4::operator*= (const mat4 &m)       { return multiply(m);     }
vec3  mat4::operator*= (const vec3 &v) const { return multiply(v);     }
vec4  mat4::operator*= (const vec4 &v) const { return multiply(v);     }

mat4  operator* (mat4 m1, const mat4 &m2)    { return m1.multiply(m2); }
vec3  operator* (mat4 m,  const vec3 &v)     { return m.multiply(v);   }
vec4  operator* (mat4 m,  const vec4 &v)     { return m.multiply(v);   }

/*// ==== DEPRECATE ======================================================= ////

mat4& mat4::multiply (const mat4& m) {
	for (unsigned int c = 0; c < 4; c++) {
		for (unsigned int r = 0; r < 4; r++)  {
			for (unsigned int e = 0; e < 4; e++) {
				elements[r+c*4] += elements[r+e*4] * m.elements[e+c*4];
			}
		}
	}
	return *this;
}

//// ==== end:DEPRECATE =================================================== //*/
