#include "ShaderManager.h"
#include <fstream>
#include <sstream>
#include <vector>

namespace managers {

static const std::string PATH_PREFIX = "../shaders/";

bool ShaderManager::loadShader(const string& filename, string& shader) {
	bool res = false;

	if(m_shaderMap.find(filename) != m_shaderMap.end())
	{
		shader = m_shaderMap.at(filename);
		res = true;
	}
	else if (loadFileContents(PATH_PREFIX + filename, shader)) {
			res = true;
			m_shaderMap.insert(pair<string, string>(filename, shader));
	}

	return res;
}

bool ShaderManager::loadFileContents(const string& fileName, string &out) {
	bool res = false;
	ifstream file;
	file.open(fileName.c_str());
	if(file.is_open()) {
		res = true;
		ostringstream out_stream;
		out_stream << file.rdbuf();
		out = out_stream.str();
	}
	return res;
}
}
