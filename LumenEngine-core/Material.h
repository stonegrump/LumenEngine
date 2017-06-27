#pragma once
#include <string>
class Material
{
	char **m_shaderPaths;
	unsigned m_numOfShaders;
public:
	Material(unsigned numOfShaders, const char **shaders);
	Material(unsigned numOfShaders, std::string *shaders);
	~Material();
};

