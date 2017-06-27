#pragma once
#include "IComponent.h"
#include "Vec2.h"
#include "Vec3.h"
#include <string>
#include "Material.h"

class GameObject;

struct Vertex {
	Vec3 pos;
	Vec3 norms;
	Vec2 uvs;
	Vertex(Vec3 _pos, Vec3 _norms, Vec2 _uvs) : pos(_pos), norms(_norms), uvs(_uvs) {}
	Vertex() {

	}
};

struct Mesh {
	unsigned int numOfTextures;
	std::string *textures;
	unsigned int numOfVerts;
	Vertex *vertices;
	unsigned int numOfIndices;
	unsigned int *triIndices;

	~Mesh() {
		delete[] vertices;
		delete[] triIndices;
	}
};

class Component_StaticMesh :
	public IComponent
{
private:
	Mesh *mesh;
public:
	Component_StaticMesh();
	Component_StaticMesh(const char *meshPath, Material mat);
	~Component_StaticMesh();

	// Inherited via IComponent
	virtual void Init() override;
	virtual void Register() override;
	virtual void Update(double dt) override;
	virtual void Shutdown() override;

	Mesh *GetMesh(const char *path);

};

