#ifndef LOGGING_H
#define LOGGING_H

#include <time.h>
#include <stdio.h>
#include <mem.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define LOG_ERR(fmt, ...) { fprintf(stderr, "ERROR:"); fprintf(stderr, fmt, ##__VA_ARGS__); fprintf(stderr, "\n");}
#define LOG_INFO(fmt, ...) fprintf(stdout, fmt"\n", ##__VA_ARGS__)

static const char* GL_LOG_FILE = "gl.log";

inline bool restart_gl_log() {
	bool res = false;
	FILE* file = fopen(GL_LOG_FILE, "w+");
	if (file) {
		time_t now = time(NULL);
		char* date = ctime(&now);
		fprintf(file, "%s log. local time %s\n", GL_LOG_FILE, date);
		res = true;
	} else
		LOG_ERR("Could not open %s for writing");
	fclose(file);
	return res;
}

inline bool gl_log(const char* message, const char* filename, int line) {
	bool res = false;
	FILE* file = fopen(GL_LOG_FILE, "a+");
	if (file) {
		fprintf(file, "%s:%i %s\n", filename, line, message);
		res = true;
	} else
		LOG_ERR("Could not open %s for writing", GL_LOG_FILE);
	fclose(file);
	return res;
}

inline void log_gl_params() {
	GLenum params[] = { GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, GL_MAX_CUBE_MAP_TEXTURE_SIZE, GL_MAX_DRAW_BUFFERS, GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, GL_MAX_TEXTURE_IMAGE_UNITS,
	GL_MAX_TEXTURE_SIZE, GL_MAX_VARYING_FLOATS, GL_MAX_VERTEX_ATTRIBS, GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, GL_MAX_VERTEX_UNIFORM_COMPONENTS, GL_MAX_VIEWPORT_DIMS,
	GL_STEREO, };
	const char* names[] = { "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS", "GL_MAX_CUBE_MAP_TEXTURE_SIZE", "GL_MAX_DRAW_BUFFERS", "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
			"GL_MAX_TEXTURE_IMAGE_UNITS", "GL_MAX_TEXTURE_SIZE", "GL_MAX_VARYING_FLOATS", "GL_MAX_VERTEX_ATTRIBS", "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
			"GL_MAX_VERTEX_UNIFORM_COMPONENTS", "GL_MAX_VIEWPORT_DIMS", "GL_STEREO", };

	gl_log("GL Context Params:", __FILE__, __LINE__);
	char msg[256];
	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv(params[i], &v);
		sprintf(msg, "%s %d", names[i], v);
		gl_log(msg, __FILE__, __LINE__);
	}
	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv(params[10], v);
	sprintf(msg, "%s %i %i", names[10], v[0], v[1]);
	gl_log(msg, __FILE__, __LINE__);
	unsigned char s = 0;
	glGetBooleanv(params[11], &s);
	sprintf(msg, "%s %i", names[11], (unsigned int) s);
	gl_log(msg, __FILE__, __LINE__);
	gl_log("-----------------------------", __FILE__, __LINE__);
}

inline void printShaderCompilationOutcome(int index) {
	const int max_len = 2048;
	int actual_len = 0;
	char log[max_len];
	glGetProgramInfoLog(index, max_len, &actual_len, log);
	std::string out(log, actual_len);
	if(actual_len > 0)
		LOG_INFO("Program info log for GL index %d: %s", index, out.c_str());
}
#endif
