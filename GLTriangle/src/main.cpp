#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <assert.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "ShaderManager.h"

#ifdef WIN32
#include <windows.h>
#define sleep(x) Sleep(x)
#endif

#include "logging.h"

static const int HEIGHT = 600;
static const int WIDTH = 800;
static const char* TITLE = "Hello Triangle";


unsigned int g_vbo[2] = { 0 };
unsigned int g_vao[2] = { 0 };





void glfw_error_callback(int error, const char* description) {

	fputs(description, stderr);
	gl_log(description, __FILE__, __LINE__);
}
void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
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

void update_fps_counter(GLFWwindow* window)
{
	static double previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	if(elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		double fps = (double) frame_count / elapsed_seconds;
		std::stringstream sstream;
		sstream << "opengl @ fps: "<<std::setprecision(2) << std::fixed << fps;
		glfwSetWindowTitle(window, sstream.str().c_str());
		frame_count = 0;
	}
	frame_count++;
}

int main(int argc, char** argv) {
	int res = 0;
	using namespace managers;
	ShaderManager shader_manager;
	do {
		char message[256] = { 0 };
		snprintf(message, sizeof(message), "starting GLFW %s", glfwGetVersionString());
		assert(gl_log(message, __FILE__, __LINE__));
		glfwSetErrorCallback(glfw_error_callback);

		if (!glfwInit()) {
			LOG_ERR("Could not start GLFW");
			res = 1;
			break;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vmode = glfwGetVideoMode(monitor);
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
		if (!window) {
			LOG_ERR("Could not open a window");
			res = 1;
			break;
		}
		glfwSetWindowSizeCallback(window, glfw_window_size_callback);
		//attach context of a window to a current thread
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
		glewInit();
		log_gl_params();

		const GLubyte* renderer = glGetString(GL_RENDERER);
		const GLubyte* version = glGetString(GL_VERSION);
		fprintf(stdout, "Renderer : %s\n", renderer);
		fprintf(stdout, "OpenGL version supported : %s\n", version);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		float points_1[] = { 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, -0.5f, 0.0f, };

		float points_2[] = { -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -0.5f, -1.0f, 0.0f };

		loadShape(g_vbo, g_vao, points_1);
		loadShape(g_vbo + 1, g_vao + 1, points_2);

		const std::string file_names[] = { "vs.glsl", "fs.glsl", "fs2.glsl" };
		std::string shaders[3];
		assert(sizeof(shaders) == sizeof(file_names));

		for(int i = 0; i< sizeof(shaders) / sizeof(shaders[0]); i++)
		{
			if (!shader_manager.loadShader(file_names[i],shaders[i])) {
				res = 1;
				LOG_ERR("Unable to load shader %s", file_names[i].c_str());
				break;
			}
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
		int params = -1;
		glGetShaderiv(fs2, GL_COMPILE_STATUS, &params);
		if(params != GL_TRUE)
		{
			LOG_ERR("GL shader index %i did not compile", fs2);
			sleep(3000);
			res = 1;
			break;
		}
		printShaderCompilationOutcome(fs2);

		unsigned int shader_programme = glCreateProgram();
		//attach first pair of shaders
		glAttachShader(shader_programme, fs);
		glAttachShader(shader_programme, vs);
		glLinkProgram(shader_programme);

		unsigned int shader_programme2 = glCreateProgram();
		//attach second pair of shaders
		//fs2 takes uniform vec4 (input_color)
		glAttachShader(shader_programme2, fs2);
		glAttachShader(shader_programme2, vs);
		glLinkProgram(shader_programme2);
		GLint loc = glGetUniformLocation(shader_programme2, "input_color");

		while (!glfwWindowShouldClose(window)) {
			glClearColor(0.6, 0.6, 0.6, 0);
			update_fps_counter (window);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(shader_programme);
			glBindVertexArray(g_vao[0]);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glUseProgram(shader_programme2);
			glUniform4d(loc, 1.0, 1.0, 0, 1.0);
			glBindVertexArray(g_vao[1]);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glfwPollEvents();
			glfwSwapBuffers(window);
			if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, 1);
			}
		}

		break;
	} while (1);
	glfwTerminate();
	return res;

}
