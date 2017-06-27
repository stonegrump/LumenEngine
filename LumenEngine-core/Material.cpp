#include "Material.h"

Material::Material(unsigned numOfShaders, const char ** shaders)
{
	m_numOfShaders = numOfShaders;
	m_shaderPaths = new char*[numOfShaders];
	for (unsigned i = 0; i < numOfShaders; ++i) {
		unsigned len = strlen(shaders[i]) + 1;
		m_shaderPaths[i] = new char[len];
		strcpy_s(m_shaderPaths[i], len, shaders[i]);
	}
}

Material::Material(unsigned numOfShaders, std::string * shaders)
{
	m_numOfShaders = numOfShaders;
	m_shaderPaths = new char*[numOfShaders];
	for (unsigned i = 0; i < numOfShaders; ++i) {
		unsigned len = shaders[i].length() + 1;
		m_shaderPaths[i] = new char[len];
		strcpy_s(m_shaderPaths[i], len, shaders[i].c_str());
	}
}

Material::~Material()
{
	for (unsigned i = 0; i < m_numOfShaders; ++i)
		delete[] m_shaderPaths[i];
	delete[] m_shaderPaths;
}
