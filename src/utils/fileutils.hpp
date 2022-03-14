#pragma once

#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

std::string read_file (const char* filepath) {
	FILE* file = fopen(filepath, "rt");
	fseek(file, 0, SEEK_END);
	unsigned long lenght = ftell(file);
	char* data = new char[lenght + 1];
	memset(data, 0, lenght + 1);
	fseek(file, 0, SEEK_SET);
	fread(data, 1, lenght, file);
	fclose(file);
	
	std::string result(data);
	delete[] data;
	return result;
}

std::string read_file2(std::string const &filepath) {
	FILE* file = fopen(filepath.c_str(), "rb");
	//if (file == nullptr)
	//	SP_ASSERT(file, "Could not open file '", filepath, "'!");
	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	//SP_ASSERT(length < 100 * 1024 * 1024);
	std::string result(length, 0);
	fseek(file, 0, SEEK_SET);
	fread(&result[0], 1, length, file);
	fclose(file);
	
	// Strip carriage returns
	result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
	return result;
}

const char* read_file3(std::string const &filepath) {
	std::string shaderCode;
	std::ifstream shaderStream(filepath, std::ios::in);
	if(shaderStream.is_open()){
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	} else {
		/*logManager->write(Log::LOG_ERROR, "Impossible to open %s. \
		                  Are you in the right directory? \
		                 Don't forget to read the FAQ !", filepath);
		return false;*/
	}
	const char* sourcePointer = shaderCode.c_str();
	return sourcePointer;
}
