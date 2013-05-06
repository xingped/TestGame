#include "common.h"

#include <GL/glew.h>
#include "shaders.h"
#include <glm/glm.hpp>

class Graphics
{
	public:
		std::map<std::string, CShaderProgram*> ShaderProgram;
	
		Graphics();
		int init_glew();
		bool createShader();
		bool newShader(std::string name);
		void terminate();
};