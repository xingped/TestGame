#include "gameobj.hpp"
#include "graphics.hpp"

float vertPos[] = {
	// top
	-1, 1, -1,
	-1, 1, 1,
	1, 1, 1,
	
	-1, 1, -1,
	1, 1, -1,
	1, 1, 1,
	
	// bot
	-1, -1, 1,
	-1, -1, -1,
	1, -1, -1,
	
	-1, -1, 1,
	1, -1, 1,
	1, -1, -1,
	
	// front
	-1, -1, -1,
	-1, 1, -1,
	1, 1, -1,
	
	-1, -1, -1,
	1, -1, -1,
	1, 1, -1,
	
	// front right
	1, -1, -1,
	1, 1, -1,
	1, 1, 1,
	
	1, -1, -1,
	1, -1, 1,
	1, 1, 1,
	
	// back
	1, -1, 1,
	1, 1, 1,
	-1, 1, 1,
	
	1, -1, 1,
	-1, -1, 1,
	-1, 1, 1,
	
	// front left
	-1, -1, 1,
	-1, 1, 1,
	-1, 1, -1,
	
	-1, -1, 1,
	-1, -1, -1,
	-1, 1, -1
};

float texCoord[] = {
	0, 0,
	0, 1,
	1, 1,
	1, 1,
	1, 0,
	0, 0,
	
	0, 0,
	0, 1,
	1, 1,
	1, 1,
	1, 0,
	0, 0,
	
	0, 0,
	0, 1,
	1, 1,
	1, 1,
	1, 0,
	0, 0,
	
	0, 0,
	0, 1,
	1, 1,
	1, 1,
	1, 0,
	0, 0,
	
	0, 0,
	0, 1,
	1, 1,
	1, 1,
	1, 0,
	0, 0,
	
	0, 0,
	0, 1,
	1, 1,
	1, 1,
	1, 0,
	0, 0
};

float vertTri[] = {
	-1, -1, 0,
	1, -1, 0,
	0, 1, 0
};

GLuint VBO;

GameObj::GameObj()
{

}

void GameObj::create()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPos), vertPos, GL_STATIC_DRAW);
	
	return;
}

void GameObj::destroy()
{
	
	return;
}

void GameObj::update()
{
	
	return;
}

void GameObj::draw(Graphics *graphics)
{
	// Check ARB_framebuffer_object spec for drawing to texture before using the next program
	// Check EXT_transform_feedback spec for passing output of one shader program into the next
	
	// Draw with red shader
	graphics->ShaderProgram["std"]->useProgram(true);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(graphics->mode, 0, 36);
	
	glDisableVertexAttribArray(0);
	graphics->ShaderProgram["std"]->useProgram(false);
	
	return;
}