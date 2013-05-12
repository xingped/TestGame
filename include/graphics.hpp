#include "common.h"

#include <GL/glew.h>
#include "shaders.h"
#include <glm/glm.hpp>

class Graphics
{
	public:
		std::map<std::string, CShaderProgram*> ShaderProgram;
		std::map<std::string, GLuint> Uniforms;
		GLenum mode;
	
		Graphics();
		int init_glew();
		bool createShader();
		bool newShader(std::string name);
		bool newUniform(std::string pName, std::string uName);
		void terminate();
};