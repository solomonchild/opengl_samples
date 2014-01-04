#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#ifdef WIN32
	#include <windows.h>
	#define sleep(x) Sleep(x)
#endif

static const int HEIGHT = 600;
static const int WIDTH = 800;
static const char* TITLE = "Hello Triangle";

int main(int argc, char** argv) {
	int res = 0;
	do {
		if (!glfwInit()) {
			fprintf(stderr, "ERROR: Could not start GLFW");
			res = 1;
			break;
		}

		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
		if (!window) {
			fprintf(stderr, "ERROR: could not open a window");
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

		float points[] = {
				0.0f, 0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f
		};
		unsigned int vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

		unsigned int vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*) NULL);

		const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		"	gl_Position = ve4 (vp, 1.0);"
		"}";

		const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main () {"
		"	frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader, NULL);
		glCompileShader(vs);
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader, NULL);
		glCompileShader(fs);

		unsigned int shader_programme = glCreateProgram();
		glAttachShader(shader_programme, fs);
		glAttachShader(shader_programme, vs);
		glLinkProgram(shader_programme);


		while(!glfwWindowShouldClose(window)){
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
