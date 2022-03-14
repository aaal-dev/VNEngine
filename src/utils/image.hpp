#pragma once

// stb
#include "stb/stb_image.h"

inline unsigned char* readImageData (const char* filepath, int &width, int &height, int &cpp) {
	stbi_set_flip_vertically_on_load(true);
	return stbi_load(filepath, &width, &height, &cpp, 0);
}

inline void freeImageData (unsigned char* data) {
	stbi_image_free(data);
}
