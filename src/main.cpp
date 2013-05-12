#include "common.h"

#include "graphics.hpp"
#include "gameobj.hpp"
#include <GL/glfw.h>

#include "AntTweakBar.h"

void init();
void setup_glfw();
void loop();
void KeyHandler();
void GLFWCALL handleResize(int width, int height);
void Shut_Down(int return_code);
void setup_tweak();

Graphics *graphics;
GameObj *cube;

TwBar *bar;

int wire = 0;
double time = 0, dt;
float triColor[] = {0.1f, 0.2f, 0.4f};

int main(void)
{
	init();
	
	loop();
	
	return(0);
}

void init()
{
	setup_glfw();
	
	setup_tweak();

	graphics = new Graphics();
	if(graphics->newShader("std") == 1) Shut_Down(1);
	
	if(graphics->newUniform("std", "inColor") == 1) Shut_Down(1);
	
	cube = new GameObj();
	cube->create();
	
	return;
}

void setup_tweak()
{
	//unsigned char triColor[] = {255, 0, 0, 128};
	TwInit(TW_OPENGL, NULL);
	
	// Create a tweak bar
    bar = TwNewBar("TweakBar");
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.
	
    // Add 'speed' to 'bar': it is a modifable (RW) variable of type TW_TYPE_DOUBLE. Its key shortcuts are [s] and [S].
    //TwAddVarRW(bar, "speed", TW_TYPE_DOUBLE, &speed, 
    //           " label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");
			   
	// Add 'wire' to 'bar': it is a modifable variable of type TW_TYPE_BOOL32 (32 bits boolean). Its key shortcut is [w].
    TwAddVarRW(bar, "wire", TW_TYPE_BOOL32, &wire, 
               " label='Wireframe mode' key=w help='Toggle wireframe display mode.' ");

    // Add 'time' to 'bar': it is a read-only (RO) variable of type TW_TYPE_DOUBLE, with 1 precision digit
    TwAddVarRO(bar, "time", TW_TYPE_DOUBLE, &time, " label='Time' precision=1 help='Time (in seconds).' ");         

    // Add 'bgColor' to 'bar': it is a modifable variable of type TW_TYPE_COLOR3F (3 floats color)
    TwAddVarRW(bar, "triColor", TW_TYPE_COLOR3F, &triColor, " label='Triangle color' ");
	
	// Set GLFW event callbacks
    // - Redirect window size changes to the callback function WindowSizeCB
    glfwSetWindowSizeCallback(handleResize);
    // - Directly redirect GLFW mouse button events to AntTweakBar
    glfwSetMouseButtonCallback((GLFWmousebuttonfun)TwEventMouseButtonGLFW);
    // - Directly redirect GLFW mouse position events to AntTweakBar
    glfwSetMousePosCallback((GLFWmouseposfun)TwEventMousePosGLFW);
    // - Directly redirect GLFW mouse wheel events to AntTweakBar
    glfwSetMouseWheelCallback((GLFWmousewheelfun)TwEventMouseWheelGLFW);
    // - Directly redirect GLFW key events to AntTweakBar
    glfwSetKeyCallback((GLFWkeyfun)TwEventKeyGLFW);
    // - Directly redirect GLFW char events to AntTweakBar
    glfwSetCharCallback((GLFWcharfun)TwEventCharGLFW);
	
	return;
}

void loop()
{
	int running = GL_TRUE;

	while(running)
	{
		time = glfwGetTime();
		dt = glfwGetTime() - time;
		
		KeyHandler();
		
		graphics->ShaderProgram["std"]->useProgram(true);
		glUniform3f(graphics->Uniforms["std_inColor"], triColor[0], triColor[1], triColor[2]);
		graphics->ShaderProgram["std"]->useProgram(false);
		
		cube->draw(graphics);
		
		// Draw tweak bars
		TwDraw();
		
		// Present frame buffer
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
		
	if (wire == 1)
		graphics->mode = GL_LINES;
	else
		graphics->mode = GL_TRIANGLES;
}

void GLFWCALL handleResize(int width, int height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	TwWindowSize(width, height);
	
	return;
}

void Shut_Down(int return_code)
{
	graphics->terminate();
	TwTerminate();
    glfwTerminate();
	
	char test;
	std::cin >> test;
	
    exit(return_code);
}