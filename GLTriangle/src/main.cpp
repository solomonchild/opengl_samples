#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#ifdef WIN32
#include <windows.h>
#define sleep(x) Sleep(x)
#endif

#define LOG_ERR(x) print_error(x)
#define LOG_STR(x) fprintf(stdout, #x" :%s\n", x)
#define LOG_INT(x) fprintf(stdout, #x": %d\n", x)

static const int HEIGHT = 600;
static const int WIDTH = 800;
static const char* TITLE = "Hello Triangle";
static const std::string PATH_PREFIX = "../shaders/";

unsigned int vbo[2] = { 0 };
unsigned int vao[2] = { 0 };

bool loadFileContents(const std::string& fileName, std::string &out) {
	bool res = false;
	FILE* file = fopen(fileName.c_str(), "r");
	char buf[128] = { 0 };
	if (file) {
		while (fread(buf, 1, sizeof(buf), file))
			out += std::string(buf);
		res = true;
	}
	fclose(file);
	return res;
}

bool loadShaders(std::vector<std::string>& shaders, const std::vector<std::string>& filenames) {
	bool res = true;
	int index = 0;

	for (std::vector<std::string>::iterator p = shaders.begin(); p != shaders.end(); p++, index++) {
		if(!loadFileContents(PATH_PREFIX + filenames[index], *p))
		{
			res = false;
			break;
		}
	}

	return res;
}

void print_error(const char *msg) {
std::cerr << "ERROR:" << msg << std::endl;
}

void loadShape(unsigned int* vbo, unsigned int *vao, float* points) {

glGenBuffers(1, vbo);
glBindBuffer(GL_ARRAY_BUFFER, *vbo);
glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points,
GL_STATIC_DRAW);

glGenVertexArrays(1, vao);
glBindVertexArray(*vao);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, *vbo);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);
}

int main(int argc, char** argv) {
int res = 0;
do {
	if (!glfwInit()) {
		LOG_ERR("Could not start GLFW");
		res = 1;
		break;
	}

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!window) {
		LOG_ERR("Could not open a window");
		res = 1;
		break;
	}
	//attach context of a window to a current thread
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	fprintf(stdout, "Renderer : %s\n", renderer);
	fprintf(stdout, "OpenGL version supported : %s\n", version);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float points_1[] = { 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, -0.5f, 0.0f, };

	float points_2[] = { -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -0.5f, -1.0f, 0.0f};

	loadShape(vbo, vao, points_1);
	loadShape(vbo + 1, vao + 1, points_2);


	const std::string arr_names[] = { "vs.glsl", "fs.glsl", "fs2.glsl" };
	std::vector<std::string> shaders(3);
	std::vector<std::string> file_names(arr_names, arr_names + sizeof(arr_names) / sizeof(arr_names[0]));

	if (!loadShaders(shaders, file_names)) {
		res = 1;
		LOG_ERR("Unable to load shaders");
		break;
	}

	const char *p_vertex_shader = shaders[0].c_str();
	const char *p_fragment_shader = shaders[1].c_str();
	const char *p_fragment_shader2 = shaders[2].c_str();

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &p_vertex_shader, NULL);
	glCompileShader(vs);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &p_fragment_shader, NULL);
	glCompileShader(fs);
	unsigned int fs2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs2, 1, &p_fragment_shader2, NULL);
	glCompileShader(fs2);

	unsigned int shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	unsigned int shader_programme2 = glCreateProgram();
	glAttachShader(shader_programme2, fs2);
	glAttachShader(shader_programme2, vs);
	glLinkProgram(shader_programme2);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.6, 0.6, 0.6, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glUseProgram(shader_programme2);
		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	break;
} while (1);

sleep(5000);

glfwTerminate();
return res;

}
