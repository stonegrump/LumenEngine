#include <cstdio>
#include <stdlib.h>

#include <cmath>

#define GLM_FORCE_RADIANS 1
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <SDL.h>

#include "Glad\glad.h"
#include <string>
#include <fstream>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4x4.h"
#include "LeMath.h"

#include <fstream>

struct Vertex {
	Vec3 pos;
	Vec3 norms;
	Vec2 uvs;
	Vertex(Vec4 _pos, Vec4 _norms, Vec2 _uvs) : pos(_pos), norms(_norms), uvs(_uvs){}
	Vertex() {
		
	}
};

struct MeshForNow {
	unsigned int numOfVerts;
	Vertex *vertices;
	unsigned int numOfIndices;
	unsigned int *triIndices;

	~MeshForNow() {
		delete[] vertices;
		delete[] triIndices;
	}
};

static const int SCREEN_FULLSCREEN = 0;
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;
static SDL_Window *window = nullptr;
static SDL_GLContext mainContext;

static MeshForNow *meshYo = nullptr;

static GLuint mainProgram;

GLuint vertexBuffer;
GLuint indexBuffer;


static void SDLDie(const char *message) {
	fprintf(stderr, "%s: %s\n:", message, SDL_GetError());
	system("pause");
	exit(2);
}

static GLchar *GetShader(const GLchar *path) {
	std::string in;
	std::ifstream file(path);

	if (!file.is_open()) {
		printf("Destruc!");
		return nullptr;
	}

	std::string line;
	while (!file.eof()) {
		std::getline(file, line);
		in += (line + "\n");
	}

	file.close();
	GLchar *returnVal = new GLchar[in.length() + 1];
	strcpy_s(returnVal, in.length() + 1, in.c_str());
	printf(returnVal);
	return returnVal;
}

static MeshForNow *GetMesh(const GLchar *path) {
	std::ifstream input(path, std::ios_base::binary);

	if (!input.is_open())
		return nullptr;

	MeshForNow *returnMesh = new MeshForNow();

	unsigned int tempInt = 0;
	input.read((char*)&tempInt, sizeof(unsigned int));
	char nameBuffer[256];
	input.read(nameBuffer, tempInt);

	input.read((char*)&tempInt, sizeof(unsigned int));
	for (int i = 0; i < tempInt; ++i) {
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

void InitScreen(const char *caption) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		SDLDie("couldn't initialize SDL");
	atexit(SDL_Quit);
	SDL_GL_LoadLibrary(nullptr);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	if (SCREEN_FULLSCREEN) {
		window = SDL_CreateWindow(caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
	}
	else {
		window = SDL_CreateWindow(caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	}
	if (window == nullptr)
		SDLDie("Couldn't set video mode");

	mainContext = SDL_GL_CreateContext(window);
	if (mainContext == nullptr)
		SDLDie("Failed to create OpenGL context");

	printf("GPENGL loaded!\n");
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));

	SDL_GL_SetSwapInterval(1);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0.f, 0.5f, 1.f, 1.f);
}
GLuint vao;

GLuint CreateProgram() {

	meshYo = GetMesh("../bench.mesh");

	GLuint vertexShaderID;
	/*GLuint tessControlID;
	GLuint tessEvalID;*/
	GLuint fragmentShaderID;
	GLuint program;
	
	
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * meshYo->numOfVerts, meshYo->vertices, GL_STATIC_DRAW);
	//glNamedBufferSubData(bufferName, 0, sizeof(data), data);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	/*glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);*/
	glEnableVertexAttribArray(0);

	glCreateBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * meshYo->numOfIndices, meshYo->triIndices, GL_STATIC_DRAW);

	/*glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, col));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glVertexArrayVertexBuffer(vao, 0, bufferName, 0, sizeof(Vec4)); */


	static const GLchar *vertexShader = GetShader("VertexShader.vs");

	

	

	static const GLchar *fragmentShader = GetShader("FragmentShader.vs");

	program = glCreateProgram();

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
	glCompileShader(vertexShaderID);
	glAttachShader(program, vertexShaderID);
	glDeleteShader(vertexShaderID);

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShader, nullptr);
	glCompileShader(fragmentShaderID);

	glAttachShader(program, fragmentShaderID);
	glLinkProgram(program);

	glDeleteShader(fragmentShaderID);

	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return program;
}

bool keypressed = false;

void Render(Uint32 time) {

	static float one = 1.0f;

	float seconds = ((float)time / 1000.0f);
	float secondsish = ((float)time / 500.0f);
	const GLfloat color[]{ sin(secondsish) * 0.25f + 0.1f, sin(seconds) * 0.25f + 0.1f, cos(seconds) * 0.25f + 0.1f, 1.f };
	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	GLfloat offset[]{ sin(seconds) * 0.5f, cos(seconds) * 0.5f, 0.f, 0.f };
	GLfloat triColor[]{ 1.f, 1.f, 1.f, 0.f };

	glUseProgram(mainProgram);

	float f = seconds * ((float)LePI * 0.1f);
	Matrix4x4 projMatrix;
	LeMath::CreatePerspectiveMatrix(50.f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f, &projMatrix);
	//LeMath::CreateFrustumMatrix(100.f, 100.f, 100.f, 100.f, 0.1f, 1000.f, &projMatrix);
	//LeMath::CreateOrthoMatrix(200, 200, 200, 200, 0.1f, 1000, &projMatrix);
	Matrix4x4 posMatrix = LeMath::CreateTranslationMatrix(0, 0, -20) * LeMath::CreateTranslationMatrix(sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f, sinf(1.3f * f) * cosf(1.5f * f) * 2.f) * LeMath::CreateRotationMatrix(EAxis::y, secondsish) * LeMath::CreateRotationMatrix(EAxis::x, seconds);



	glUniformMatrix4fv(glGetUniformLocation(mainProgram, "projMat"), 1, GL_FALSE, projMatrix.GetArray());
	glUniformMatrix4fv(glGetUniformLocation(mainProgram, "tranMat"), 1, GL_FALSE, posMatrix.GetArray());

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, meshYo->numOfIndices, GL_UNSIGNED_INT, 0);
}

int main(int argv, char** argc)
{
	InitScreen("OpenGL 4.5");

	mainProgram = CreateProgram();
	GLuint vertexArray;


	glCreateVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	SDL_Event event;
	bool quit = false;


	while (!quit) {

		Render(SDL_GetTicks());
		SDL_GL_SwapWindow(window);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				else
					keypressed = !keypressed;
			}
		}
	}

	glDeleteVertexArrays(1, &vertexArray);
	glDeleteProgram(mainProgram);

	return 0;
}

/*const Vec4 cubeData[]{

Vec4(0.25f,  0.25f, -0.25f, 1.0f),
Vec4(0.25f, -0.25f, -0.25f, 1.0f),
Vec4(-0.25f, -0.25f, -0.25f, 1.0f),

Vec4(-0.25f, -0.25f, -0.25f, 1.0f),
Vec4(-0.25f,  0.25f, -0.25f, 1.0f),
Vec4(0.25f,  0.25f, -0.25f, 1.0f),

Vec4(-0.25f,  0.25f, -0.25f, 1.0f),
Vec4(-0.25f, -0.25f, -0.25f, 1.0f),
Vec4(-0.25f, -0.25f,  0.25f, 1.0f),

Vec4(-0.25f, -0.25f,  0.25f, 1.0f),
Vec4(-0.25f,  0.25f,  0.25f, 1.0f),
Vec4(-0.25f,  0.25f, -0.25f, 1.0f),

Vec4(0.25f,  0.25f,  0.25f, 1.0f),
Vec4(0.25f, -0.25f,  0.25f, 1.0f),
Vec4(0.25f, -0.25f, -0.25f, 1.0f),

Vec4(0.25f, -0.25f, -0.25f, 1.0f),
Vec4(0.25f,  0.25f, -0.25f, 1.0f),
Vec4(0.25f,  0.25f,  0.25f, 1.0f),


Vec4(-0.25f,  -0.25f, 0.25f, 1.0f),
Vec4(-0.25f,  -0.25f,  -0.25f, 1.0f),
Vec4(0.25f,  -0.25f,  -0.25f, 1.0f),

Vec4(0.25f,  -0.25f,  -0.25f, 1.0f),
Vec4(0.25f,  -0.25f, 0.25f, 1.0f),
Vec4(-0.25f,  -0.25f, 0.25f, 1.0f),

Vec4( 0.25f,  0.25f, -0.25f, 1.0f),
Vec4(-0.25f,  0.25f, -0.25f, 1.0f),
Vec4(-0.25f,  0.25f,  0.25f, 1.0f),

Vec4(-0.25f,  0.25f,  0.25f, 1.0f),
Vec4(0.25f,  0.25f,  0.25f, 1.0f),
Vec4(0.25f,  0.25f, -0.25f, 1.0f),


Vec4(0.25f, -0.25f, 0.25f, 1.0f),
Vec4(0.25f,  0.25f, 0.25f, 1.0f),
Vec4(-0.25f, 0.25f, 0.25f, 1.0f),

Vec4(-0.25f,  0.25f, 0.25f, 1.0f),
Vec4(-0.25f, -0.25f, 0.25f, 1.0f),
Vec4(0.25f, -0.25f, 0.25f, 1.0f),
};*/

/*[]{
"#version 450 core  \n"
"layout (location = 0) in vec4 position; \n"
"layout (location = 1) in vec4 offset; \n"
"layout (location = 2) in vec4 color; \n"
"                                     \n"
"out vec4 vsColor; \n"
"void main(void) { \n"
"const vec4 colors[3] = vec4[3](vec4(1, 1, 0, 1.0), vec4(0, 1, 1, 1.0), vec4(1, 1, 1, 1.0));\n"
"gl_Position = position + offset;\n"
"vsColor = colors[gl_VertexID]; \n"
"}\n"
};
static const GLchar *tessControl[]{
"#version 410 core  \n"
"layout (vertices = 3) out; \n"
"                                     \n"
"void main(void) { \n"
"	if(gl_InvocationID == 0){          \n"
"		gl_TessLevelInner[0] = 5.0;          \n"
"		gl_TessLevelOuter[0] = 5.0;       \n"
"		gl_TessLevelOuter[1] = 5.0;       \n"
"		gl_TessLevelOuter[2] = 5.0;       \n"
"	}          \n"
"	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"
"}\n"
};

static const char * tcs_source[] =
{
"#version 450 core                                                                 \n"
"                                                                                  \n"
"layout (vertices = 3) out;                                                        \n"
"                                                                                  \n"
"void main(void)                                                                   \n"
"{                                                                                 \n"
"    if (gl_InvocationID == 0)                                                     \n"
"    {                                                                             \n"
"        gl_TessLevelInner[0] = 10.0;                                               \n"
"        gl_TessLevelOuter[0] = 10.0;                                               \n"
"        gl_TessLevelOuter[1] = 10.0;                                               \n"
"        gl_TessLevelOuter[2] = 10.0;                                               \n"
"    }                                                                             \n"
"    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     \n"
"}                                                                                 \n"

};

static const char * tes_source[] =
{
"#version 450 core                                                                 \n"
"                                                                                  \n"
"layout (triangles, equal_spacing, cw) in;                                         \n"
"                                                                                  \n"
"void main(void)                                                                   \n"
"{                                                                                 \n"
"    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
"                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
"                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
"}                                                                                 \n"
};

static const char * geo_source[] =
{
"#version 410 core                                                                 \n"
"                                                                                  \n"
"layout (triangles) in;                                         \n"
"layout (points, max_vertices = 3) out;                                         \n"
"                                                                                  \n"
"void main(void)                                                                   \n"
"{                                                                                 \n"
"	int i;\n"
"	for(i = 0; i < gl_in.length(); i++){                                                                                 \n"
"       gl_Position = gl_in[i].gl_Position;                                                                          \n"
"       EmitVertex();                                                                          \n"
"	}                                                                                 \n"
"}                                                                                 \n"
};

static const GLchar *tessEval[]{
"#version 410 core  \n"
"layout (triangles, equal_spacing, cw) in; \n"
"                                     \n"
"void main(void) { \n"
"	gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position + gl_TessCoord.y * gl_in[1].gl_Position + gl_TessCoord.z * gl_in[2].gl_Position);   \n"
"}\n"
};

*/