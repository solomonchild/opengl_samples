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

const static int SHAPE_COUNT = 2;
unsigned int g_vbo[SHAPE_COUNT] = { 0 };
unsigned int g_vao[SHAPE_COUNT] = { 0 };



void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
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
	managers::ShaderManager shader_manager;


	float points[] = {
			0.0f, 0.5f, 0.0f,
			0.0f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
	};

	float colours[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
	};



	do {

		std::cout << "Starting GLFW " << glfwGetVersionString() << std::endl;


		if (!glfwInit()) {
			LOG_ERR("Could not start GLFW");
			res = 1;
			break;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
		if (!window) {
					LOG_ERR("Could not open a window");
					res = 1;
					break;
		}
		glfwSetWindowSizeCallback(window, glfw_window_size_callback);
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;

		glewInit();

		unsigned int points_vbo,colours_vbo;
		points_vbo = colours_vbo = 0;

		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

		glGenBuffers(1, &colours_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
		glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), colours, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		//enable attribute arrays for later use
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		GLuint vs;
		GLuint fs;
		std::string s_fs;
		std::string s_vs;

		vs = glCreateShader(GL_VERTEX_SHADER);
		shader_manager.loadShader("vs.glsl",s_vs);
		const char* p_vs = s_vs.c_str();
		glShaderSource(vs, 1, &p_vs, NULL);
		glCompileShader(vs);

		fs = glCreateShader(GL_FRAGMENT_SHADER);
		shader_manager.loadShader("fs.glsl",s_fs);
		const char* p_fs = s_fs.c_str();
		glShaderSource(fs, 1, &p_fs, NULL);
		glCompileShader(fs);

		printShaderCompilationOutcome(fs);
		printShaderCompilationOutcome(vs);

		GLuint prog = glCreateProgram();
		glAttachShader(prog, fs);
		glAttachShader(prog, vs);
		glLinkProgram(prog);
		glUseProgram(prog);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		while (!glfwWindowShouldClose(window)) {
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glfwPollEvents();
			glfwSwapBuffers(window);

			if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
				glfwSetWindowShouldClose(window, 1);
			}
		}

		break;
	} while (1); //do loop

	glfwTerminate();
	return res;

}
