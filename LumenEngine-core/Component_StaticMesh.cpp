#include "Component_StaticMesh.h"
#include <fstream>
#include "Lodepng\lodepng.h"


Component_StaticMesh::Component_StaticMesh()
{
}


Component_StaticMesh::~Component_StaticMesh()
{
}

void Component_StaticMesh::Init()
{
}

void Component_StaticMesh::Register()
{
}

void Component_StaticMesh::Update(double dt)
{
}

void Component_StaticMesh::Shutdown()
{
}

Mesh *Component_StaticMesh::GetMesh(const char *path) {
	std::ifstream input(path, std::ios_base::binary);

	if (!input.is_open())
		return nullptr;

	Mesh *returnMesh = new Mesh();

	unsigned int tempInt = 0;
	input.read((char*)&tempInt, sizeof(unsigned int));
	char nameBuffer[256];
	input.read(nameBuffer, tempInt);

	input.read((char*)&tempInt, sizeof(unsigned int));
	for (unsigned i = 0; i < tempInt; ++i) {
		unsigned int tempTexNameLen;
		input.read((char*)&tempTexNameLen, sizeof(unsigned int));
		input.read(nameBuffer, tempTexNameLen);
	}

	input.read((char*)&tempInt, sizeof(unsigned int));
	returnMesh->vertices = new Vertex[tempInt];
	input.read((char*)returnMesh->vertices, sizeof(Vertex) * tempInt);
	returnMesh->numOfVerts = tempInt;

	input.read((char*)&tempInt, sizeof(unsigned int));
	tempInt *= 3;
	returnMesh->triIndices = new unsigned int[tempInt];
	input.read((char*)returnMesh->triIndices, sizeof(unsigned int) * tempInt);
	returnMesh->numOfIndices = tempInt;

	return returnMesh;
}
