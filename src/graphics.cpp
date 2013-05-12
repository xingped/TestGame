#include "graphics.hpp"
#include <GL/glfw.h>
#include <iostream>

Graphics::Graphics()
{

}

int Graphics::init_glew()
{
	// Initialize GLEW
	GLenum glewInitError = glewInit();
	
	if(glewInitError != GLEW_OK)
	{
		std::cout << "GLEW Init Failure: " << glewGetErrorString(glewInitError) << std::endl;
		return(1);
	}
	
	mode = GL_TRIANGLES;
	
	return(0);
}

bool Graphics::newShader(std::string name)
{
	ShaderProgram[name] = new CShaderProgram();
	CShader* vertShader = new CShader();
	CShader* fragShader = new CShader();
	
	ShaderProgram[name]->createProgram();
	// Create and load shaders
	if (vertShader->loadShader("shaders/"+name+".vert", GL_VERTEX_SHADER) == 1) return(1);
	if (fragShader->loadShader("shaders/"+name+".frag", GL_FRAGMENT_SHADER) == 1) return(1);
	
	// Attach shaders to shader program
	ShaderProgram[name]->addShaderToProgram(vertShader);
	ShaderProgram[name]->addShaderToProgram(fragShader);
	
	if (ShaderProgram[name]->linkProgram() == 1) return(1);
	if (ShaderProgram[name]->validateProgram() == 1) return(1);
	
	vertShader->deleteShader();
	fragShader->deleteShader();
	
	return(0);
}

void Graphics::terminate()
{
	for(std::map<std::string, CShaderProgram*>::const_iterator i = ShaderProgram.begin(); i != ShaderProgram.end(); i++)
	{
		std::string key = i->first;
		ShaderProgram[key]->deleteProgram();
	}
	
	return;
}