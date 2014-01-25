#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#include<map>
#include <string>
#include "logging.h"

namespace managers {
using namespace std;
class ShaderManager {
public:
	ShaderManager() {
	}

	~ShaderManager() {
	}

	bool loadShader(const string& filename, std::string& shader);
protected:
	map<string, string> m_shaderMap;
	bool loadFileContents(const string& fileName, string &out);

};
}
#endif
