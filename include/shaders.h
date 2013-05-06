#include "common.h"

/********************************

Class:	CShader

Purpose:	Wraps OpenGL shader loading
			and compiling.

********************************/

class CShader
{
	public:
		bool loadShader(std::string sFile, int a_iType);
		void deleteShader();

		bool isLoaded();
		unsigned int getShaderID();

		CShader();

	private:
		unsigned int uiShader; // ID of shader
		int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
		bool bLoaded; // Whether shader was loaded and compiled
};

/********************************

Class:	CShaderProgram

Purpose:	Wraps OpenGL shader program
			and make its usage easy.

********************************/

class CShaderProgram
{
	public:
		void createProgram();
		void deleteProgram();

		bool addShaderToProgram(CShader* shShader);
		bool linkProgram();

		void useProgram(bool state);
		
		bool validateProgram();

		unsigned int getProgramID();

		CShaderProgram();

	private:
		unsigned int uiProgram; // ID of program
		bool bLinked; // Whether program was linked and is ready to use
};