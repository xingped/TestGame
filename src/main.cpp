#include "common.h"

#include "graphics.hpp"
#include "gameobj.hpp"
#include <GL/glfw.h>

void init();
void setup_glfw();
void loop();
void KeyHandler();
void GLFWCALL handleResize(int width, int height);
void Shut_Down(int return_code);

Graphics *graphics;
GameObj *cube;



int main(void)
{
	init();
	
	loop();
	
	return(0);
}

void init()
{
	setup_glfw();

	graphics = new Graphics();
	if(graphics->newShader("red") == 1) Shut_Down(1);
	if(graphics->newShader("green") == 1) Shut_Down(1);
	
	cube = new GameObj();
	cube->create();
	
	graphics->ShaderProgram["red"]->useProgram(true);
	
	return;
}

void loop()
{
	int running = GL_TRUE;

	while(running)
	{
		KeyHandler();
		cube->draw(graphics);
		
		glfwSwapBuffers();
		
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}
	
	return;
}

void setup_glfw()
{
    const int window_width = 800, window_height = 600;
 
    if (glfwInit() != GL_TRUE)
	{
        Shut_Down(1);
	}
	
    // 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
	if (!glfwOpenWindow(window_width, window_height, 5, 6, 5, 1, 1, 1, GLFW_WINDOW))
        Shut_Down(1);
    
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	
	glfwSetWindowSizeCallback(handleResize);
	
    glfwSetWindowTitle("Test Game!");
	
	// Initialize GLEW
	GLenum glewInitError = glewInit();
	
	if(glewInitError != GLEW_OK)
	{
		printf("GLEW Init Failure: %s\n", glewGetErrorString(glewInitError));
		Shut_Down(1);
	}
	
	return;
	
	return;
}

void KeyHandler()
{
	glfwPollEvents();
	
	// escape to quit
	if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		Shut_Down(0);
}

void GLFWCALL handleResize(int width, int height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	
	return;
}

void Shut_Down(int return_code)
{
	graphics->terminate();
    glfwTerminate();
	
	char test;
	std::cin >> test;
	
    exit(return_code);
}