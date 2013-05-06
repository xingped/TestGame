#include "shaders.h"
#include <GL/glew.h>

CShader::CShader()
{
	bLoaded = false;
}

/*-----------------------------------------------

Name:		loadShader

Params:	sFile - path to a file
			a_iType - type of shader (fragment, vertex, geometry)

Result:	Loads and compiles shader.

-----------------------------------------------*/

bool CShader::loadShader(std::string sFile, int a_iType)
{
	FILE* fp = fopen(sFile.c_str(), "rt");
	if (!fp)
		return false;

	// Get all lines from a file

	std::vector<std::string> sLines;
	char sLine[255];
	
	while(fgets(sLine, 255, fp))
		sLines.push_back(sLine);
	
	fclose(fp);

	const char** sProgram = new const char*[(int)sLines.size()];
	
	for(int i=0; i < (int)sLines.size(); i++)
		sProgram[i] = sLines[i].c_str();
	
	uiShader = glCreateShader(a_iType);
	
	if (uiShader == 0) {
        std::cout << "Error creating shader type " << a_iType << std::endl;
        return(1);
    }

	glShaderSource(uiShader, (int)sLines.size(), sProgram, NULL);
	glCompileShader(uiShader);

	delete[] sProgram;

	int iCompilationStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);
	
	if(!iCompilationStatus)
	{
		GLchar ErrorLog[1024] = {0};
		glGetShaderInfoLog(uiShader, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << "Error compiling shader type " << a_iType << ": " << ErrorLog << std::endl;
		return(1);
	}	
	
	iType = a_iType;
	bLoaded = true;

	return(0);
}

/*-----------------------------------------------

Name:		isLoaded

Params:	none

Result:	True if shader was loaded and compiled.

-----------------------------------------------*/

bool CShader::isLoaded()
{
	return bLoaded;
}

/*-----------------------------------------------

Name:		getShaderID

Params:	none

Result:	Returns ID of a generated shader.

-----------------------------------------------*/

unsigned int CShader::getShaderID()
{
	return uiShader;
}

/*-----------------------------------------------

Name:		deleteShader

Params:	none

Result:	Deletes shader and frees memory in GPU.

-----------------------------------------------*/

void CShader::deleteShader()
{
	if(!isLoaded())
		return;
		
	bLoaded = false;
	glDeleteShader(uiShader);
}

CShaderProgram::CShaderProgram()
{
	bLinked = false;
}

/*-----------------------------------------------

Name:		createProgram

Params:	none

Result:	Creates a new program.

-----------------------------------------------*/

void CShaderProgram::createProgram()
{
	uiProgram = glCreateProgram();
}

/*-----------------------------------------------

Name:		addShaderToProgram

Params:	sShader - shader to add

Result:	Adds a shader (like source file) to
			a program, but only compiled one.

-----------------------------------------------*/

bool CShaderProgram::addShaderToProgram(CShader* shShader)
{
	if(!shShader->isLoaded())
		return false;

	glAttachShader(uiProgram, shShader->getShaderID());

	return true;
}

/*-----------------------------------------------

Name:		linkProgram

Params:	none

Result:	Performs final linkage of OpenGL program.

-----------------------------------------------*/

bool CShaderProgram::linkProgram()
{
	GLchar ErrorLog[1024] = { 0 };
	int success;
	
	glLinkProgram(uiProgram);
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(uiProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << "Error linking shader program: " << ErrorLog << std::endl;
		return(1);
	}
	
	bLinked = true;
	
	return(0);
}

/*-----------------------------------------------

Name:		validateProgram

Params:	none

Result:	Performs validation of OpenGL program.

-----------------------------------------------*/

bool CShaderProgram::validateProgram()
{
	GLchar ErrorLog[1024] = { 0 };
	int success;
	
	glValidateProgram(uiProgram);
	glGetProgramiv(uiProgram, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(uiProgram, sizeof(ErrorLog), NULL, ErrorLog);
        std::cout << "Invalid shader program: " << ErrorLog << std::endl;
        return(1);
    }
	
	return(0);
}

/*-----------------------------------------------

Name:		deleteProgram

Params:	none

Result:	Deletes program and frees memory on GPU.

-----------------------------------------------*/

void CShaderProgram::deleteProgram()
{
	if(!bLinked)
		return;
		
	bLinked = false;
	glDeleteProgram(uiProgram);
}

/*-----------------------------------------------

Name:		useProgram

Params:	none

Result:	Tells OpenGL to use this program.

-----------------------------------------------*/

void CShaderProgram::useProgram(bool state)
{
	if(bLinked)
	{
		if(state == true)
			glUseProgram(uiProgram);
		else if(state == false)
			glUseProgram(0);
	}
}