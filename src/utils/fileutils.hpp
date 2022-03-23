#pragma once

#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

namespace FileUtils {

inline std::string read_file (const char* filepath) {
	FILE* file = fopen(filepath, "rt");
	fseek(file, 0, SEEK_END);
	unsigned long lenght = ftell(file);
	char* data = new char[lenght + 1];
	memset(data, 0, lenght + 1);
	fseek(file, 0, SEEK_SET);
	fread(data, 1, lenght, file);
	fclose(file);
	
	std::string result{data};
	delete[] data;
	return result;
};

inline std::string read_file2(std::string const &filepath) {
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
};

inline std::string readTextFile(std::string const &filepath) {
	std::ifstream file(filepath, std::ios::in);
	if (!file.is_open()) {
		return "";
	}
	std::stringstream sstr;
	sstr << file.rdbuf();
	std::string str{sstr.str()};
	file.close();
	return str;
};

inline std::string readTXTFileToString1 (std::string const &filepath) {
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
};

inline std::string readTXTFileToString2 (std::string const &filepath) {
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
};

}