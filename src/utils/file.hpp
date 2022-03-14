#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

std::string readTXTFileToString1 (std::string const &filepath) {
	FILE* file = fopen(filepath.data(), "rb");
	if (file == nullptr){
		//SP_ASSERT(file, "Could not open file '", filepath.data(), "'!");
	}
	
	fseek(file, 0, SEEK_END);
	unsigned int length = ftell(file);
	//SP_ASSERT(length < 100 * 1024 * 1024);
	std::string result(length, 0);
	fseek(file, 0, SEEK_SET);
	fread(&result[0], 1, length, file);
	fclose(file);
	
	// Strip carriage returns
	result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
	return result;
}

std::string readTXTFileToString2 (std::string const &filepath) {
	std::string result;
	std::ifstream shaderStream(filepath, std::ios::in);
	if (!shaderStream.is_open()) {
		//SP_ASSERT(file, "Could not open file '", filepath.data(), "'!");
	}
	std::stringstream sstr;
	sstr << shaderStream.rdbuf();
	result = sstr.str();
	shaderStream.close();
	
	// Strip carriage returns
	result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
	return result;
}
