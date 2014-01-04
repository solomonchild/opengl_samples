#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#define sleep(x) Sleep(x)
#endif

#define LOG_ERR(x) print_error(x)

static const int HEIGHT = 600;
static const int WIDTH = 800;
static const char* TITLE = "Hello Triangle";
static const std::string PATH_PREFIX = "../shaders/";

bool loadShaderFromFile(const char* fileName, std::string& out) {
	bool res = false;
	FILE* file = fopen((PATH_PREFIX + fileName).c_str(), "r");
	char buf[128];
	if (file) {
		while(fread(buf, sizeof(buf), 1, file))
			out += buf;
		res = true;
	}
	fclose(file);
	return res;
}

void print_error(const char *msg)
{
	std::cerr << "ERROR:" << msg << std::endl;
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

		float points[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f,
				0.0f };
		unsigned int vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points,
				GL_STATIC_DRAW);

		unsigned int vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);

		std::string vertex_shader;
		std::string fragment_shader;
		if(!loadShaderFromFile("vs.glsl", vertex_shader)
				|| !loadShaderFromFile("fs.glsl", fragment_shader))
		{
			res = 1;
			LOG_ERR("Unable to load shaders");
			break;
		}

		const char *p_vertex_shader = vertex_shader.c_str();
		const char *p_fragment_shader = fragment_shader.c_str();

		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &p_vertex_shader, NULL);
		glCompileShader(vs);
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1,  &p_fragment_shader, NULL);
		glCompileShader(fs);

		unsigned int shader_programme = glCreateProgram();
		glAttachShader(shader_programme, fs);
		glAttachShader(shader_programme, vs);
		glLinkProgram(shader_programme);

		while (!glfwWindowShouldClose(window)) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(shader_programme);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		break;
	} while (1);

	sleep(5000);

	glfwTerminate();
	return res;

}
