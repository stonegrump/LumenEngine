#include <cstdio>
#include <stdlib.h>

#include <cmath>

#define GLM_FORCE_RADIANS 1
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <SDL.h>

#include "Glad\glad.h"


static const int SCREEN_FULLSCREEN = 0;
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;
static SDL_Window *window = nullptr;
static SDL_GLContext mainContext;

static GLuint mainProgram;

GLuint bufferName;


static void SDLDie(const char *message) {
	fprintf(stderr, "%s: %s\n:", message, SDL_GetError());
	system("pause");
	exit(2);
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

	//glClear(GL_COLOR_BUFFER_BIT);
}
GLuint vao;

GLuint CreateProgram() {
	GLuint vertexShaderID;
	GLuint tessControlID;
	GLuint tessEvalID;
	GLuint fragmentShaderID;
	GLuint program;

	
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &bufferName);
	glBindBuffer(GL_ARRAY_BUFFER, bufferName);
	glNamedBufferData(bufferName, 1024 * 1024, nullptr, GL_DYNAMIC_STORAGE_BIT);
	const float data[]{
		-0.25, -0.25, 0.5, 1.0,
		0.25, -0.25, 0.5, 1.0,
		-0.25, 0.25, 0.5, 1.0
	};
	glNamedBufferSubData(bufferName, 0, sizeof(data), data);

	glVertexArrayVertexBuffer(vao, 0, bufferName, 0, sizeof(float) * 4);
	glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(vao, 0);

	static const GLchar *vertexShader[]{
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

	//static const GLchar *tessControl[]{
	//	"#version 410 core  \n"
	//	"layout (vertices = 3) out; \n"
	//	"                                     \n"
	//	"void main(void) { \n"
	//	"	if(gl_InvocationID == 0){          \n"
	//	"		gl_TessLevelInner[0] = 5.0;          \n"
	//	"		gl_TessLevelOuter[0] = 5.0;       \n"
	//	"		gl_TessLevelOuter[1] = 5.0;       \n"
	//	"		gl_TessLevelOuter[2] = 5.0;       \n"
	//	"	}          \n"
	//	"	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"
	//	"}\n"
	//};

	//static const char * tcs_source[] =
	//{
	//	"#version 450 core                                                                 \n"
	//	"                                                                                  \n"
	//	"layout (vertices = 3) out;                                                        \n"
	//	"                                                                                  \n"
	//	"void main(void)                                                                   \n"
	//	"{                                                                                 \n"
	//	"    if (gl_InvocationID == 0)                                                     \n"
	//	"    {                                                                             \n"
	//	"        gl_TessLevelInner[0] = 10.0;                                               \n"
	//	"        gl_TessLevelOuter[0] = 10.0;                                               \n"
	//	"        gl_TessLevelOuter[1] = 10.0;                                               \n"
	//	"        gl_TessLevelOuter[2] = 10.0;                                               \n"
	//	"    }                                                                             \n"
	//	"    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     \n"
	//	"}                                                                                 \n"

	//};

	//static const char * tes_source[] =
	//{
	//	"#version 450 core                                                                 \n"
	//	"                                                                                  \n"
	//	"layout (triangles, equal_spacing, cw) in;                                         \n"
	//	"                                                                                  \n"
	//	"void main(void)                                                                   \n"
	//	"{                                                                                 \n"
	//	"    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
	//	"                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
	//	"                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
	//	"}                                                                                 \n"
	//};

	//static const char * geo_source[] =
	//{
	//	"#version 410 core                                                                 \n"
	//	"                                                                                  \n"
	//	"layout (triangles) in;                                         \n"
	//	"layout (points, max_vertices = 3) out;                                         \n"
	//	"                                                                                  \n"
	//	"void main(void)                                                                   \n"
	//	"{                                                                                 \n"
	//	"	int i;\n"
	//	"	for(i = 0; i < gl_in.length(); i++){                                                                                 \n"
	//	"       gl_Position = gl_in[i].gl_Position;                                                                          \n"
	//	"       EmitVertex();                                                                          \n"
	//	"	}                                                                                 \n"
	//	"}                                                                                 \n"
	//};

	//static const GLchar *tessEval[]{
	//	"#version 410 core  \n"
	//	"layout (triangles, equal_spacing, cw) in; \n"
	//	"                                     \n"
	//	"void main(void) { \n"
	//	"	gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position + gl_TessCoord.y * gl_in[1].gl_Position + gl_TessCoord.z * gl_in[2].gl_Position);   \n"
	//	"}\n"
	//};
	static const GLchar *fragmentShader[]{
		"#version 450 core  \n"
		"in vec4 vsColor;  \n"
		"out vec4 color;  \n"
		"void main(void) { \n"
		"color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5, cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5, sin(gl_FragCoord.x * 0.15) + cos(gl_FragCoord.y * 0.15), 1);\n"
		"}\n"
	};

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, vertexShader, nullptr);
	glCompileShader(vertexShaderID);

	//tessControlID = glCreateShader(GL_TESS_CONTROL_SHADER);
	//glShaderSource(tessControlID, 1, tessControl, nullptr);
	//glCompileShader(tessControlID);

	//tessEvalID = glCreateShader(GL_TESS_EVALUATION_SHADER);
	//glShaderSource(tessEvalID, 1, tessEval, nullptr);
	//glCompileShader(tessEvalID);

	//GLuint geoShader = glCreateShader(GL_GEOMETRY_SHADER);
	//glShaderSource(geoShader, 1, geo_source, nullptr);
	//glCompileShader(geoShader);

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, fragmentShader, nullptr);
	glCompileShader(fragmentShaderID);

	program = glCreateProgram();
	glAttachShader(program, vertexShaderID);
	//glAttachShader(program, tessControlID);
	//glAttachShader(program, tessEvalID);
	//glAttachShader(program, geoShader);
	glAttachShader(program, fragmentShaderID);
	glLinkProgram(program);

	glDeleteShader(vertexShaderID);
	//glDeleteShader(tessControlID);
	//glDeleteShader(tessEvalID);
	//glDeleteShader(geoShader);
	glDeleteShader(fragmentShaderID);

	return program;
}

bool keypressed = false;

void Render(Uint32 time) {

	float seconds = ((float)time / 1000.0f);
	float secondsish = ((float)time / 500.0f);
	const GLfloat color[]{ sin(secondsish) * 0.25f + 0.1f, sin(seconds) * 0.25f + 0.1f, cos(seconds) * 0.25f + 0.1f, 1.f };
	glClearBufferfv(GL_COLOR, 0, color);

	GLfloat offset[]{ sin(seconds) * 0.5f, cos(seconds) * 0.5f, 0.f, 0.f };
	GLfloat triColor[]{ 1.f, 1.f, 1.f, 0.f };

	glUseProgram(mainProgram);

	glBindVertexArray(vao);
	glVertexAttrib4fv(1, offset);
	glVertexAttrib4fv(2, triColor);

	glDrawArrays(GL_TRIANGLES, 0, 3);
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

