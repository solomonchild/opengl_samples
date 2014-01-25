#ifndef LOGGING_H
#define LOGGING_H

#include <time.h>
#include <stdio.h>
#include <mem.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define LOG_ERR(fmt, ...) { fprintf(stderr, "ERROR:"); fprintf(stderr, fmt, ##__VA_ARGS__); fprintf(stderr, "\n");}
#define LOG_INFO(fmt, ...) fprintf(stdout, fmt"\n", ##__VA_ARGS__)


inline void printShaderCompilationOutcome(int index) {
	const int max_len = 2048;
	int actual_len = 0;
	char log[max_len];
	glGetShaderInfoLog(index, max_len, &actual_len, log);
	std::string out(log, actual_len);
	if(actual_len > 0)
		LOG_INFO("Program info log for GL index %d: %s", index, out.c_str());
}
#endif
